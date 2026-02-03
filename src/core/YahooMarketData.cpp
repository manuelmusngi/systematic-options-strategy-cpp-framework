#include "core/YahooMarketData.hpp"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <sstream>
#include <utility>

using json = nlohmann::json;

static size_t writeToString(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t total = size * nmemb;
    std::string* s = static_cast<std::string*>(userp);
    s->append(static_cast<char*>(contents), total);
    return total;
}

YahooMarketData::YahooMarketData(std::string baseUrl, std::chrono::milliseconds pollInterval)
    : baseUrl_(std::move(baseUrl)), pollInterval_(pollInterval), running_(false) {}

YahooMarketData::~YahooMarketData() { stop(); }

void YahooMarketData::subscribe(const std::string& symbol) {
    std::lock_guard<std::mutex> lk(mtx_);
    symbols_.insert(symbol);
    cv_.notify_all();
}

void YahooMarketData::unsubscribe(const std::string& symbol) {
    std::lock_guard<std::mutex> lk(mtx_);
    symbols_.erase(symbol);
}

void YahooMarketData::setQuoteCallback(QuoteCallback cb) {
    std::lock_guard<std::mutex> lk(mtx_);
    callback_ = std::move(cb);
}

void YahooMarketData::start() {
    bool expected = false;
    if (!running_.compare_exchange_strong(expected, true)) return;
    worker_ = std::thread(&YahooMarketData::runLoop, this);
}

void YahooMarketData::stop() {
    bool expected = true;
    if (!running_.compare_exchange_strong(expected, false)) return;
    cv_.notify_all();
    if (worker_.joinable()) worker_.join();
}

static std::string joinSymbols(const std::set<std::string>& syms) {
    std::string out;
    bool first = true;
    for (const auto& s : syms) {
        if (!first) out += ",";
        out += s;
        first = false;
    }
    return out;
}

void YahooMarketData::runLoop() {
    while (running_) {
        {
            std::unique_lock<std::mutex> lk(mtx_);
            if (symbols_.empty()) {
                cv_.wait_for(lk, pollInterval_, [this]{ return !symbols_.empty() || !running_; });
            }
        }
        if (!running_) break;
        fetchAndPublish();
        std::unique_lock<std::mutex> lk(mtx_);
        cv_.wait_for(lk, pollInterval_, [this]{ return !running_; });
    }
}

void YahooMarketData::fetchAndPublish() {
    std::set<std::string> symsCopy;
    {
        std::lock_guard<std::mutex> lk(mtx_);
        symsCopy = symbols_;
    }
    if (symsCopy.empty()) return;

    std::string symbolsCsv = joinSymbols(symsCopy);
    CURL* curl = curl_easy_init();
    if (!curl) return;

    std::string url = baseUrl_ + "?symbols=" + curl_easy_escape(curl, symbolsCsv.c_str(), 0);
    std::string response;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeToString);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "OptionsTradingSystem/1.0");

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "[YahooMarketData] curl error: " << curl_easy_strerror(res) << "\n";
        curl_easy_cleanup(curl);
        return;
    }
    curl_easy_cleanup(curl);

    try {
        auto j = json::parse(response);
        if (!j.contains("quoteResponse") || !j["quoteResponse"].contains("result")) return;
        auto results = j["quoteResponse"]["result"];
        for (const auto& item : results) {
            Quote q;
            if (item.contains("symbol")) q.symbol = item["symbol"].get<std::string>();
            if (item.contains("bid")) q.bid = item["bid"].get<double>();
            if (item.contains("ask")) q.ask = item["ask"].get<double>();
            if (item.contains("regularMarketPrice")) q.last = item["regularMarketPrice"].get<double>();
            if (item.contains("regularMarketTime")) {
                long t = item["regularMarketTime"].get<long>();
                q.timestamp = std::chrono::system_clock::from_time_t(t);
            } else {
                q.timestamp = std::chrono::system_clock::now();
            }
            QuoteCallback cbCopy;
            {
                std::lock_guard<std::mutex> lk(mtx_);
                cbCopy = callback_;
            }
            if (cbCopy) {
                try { cbCopy(q); } catch (...) {}
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "[YahooMarketData] json parse error: " << e.what() << "\n";
    }
}
