#pragma once
#include "core/MarketData.hpp"
#include <string>
#include <atomic>
#include <mutex>
#include <set>
#include <thread>
#include <condition_variable>

class YahooMarketData : public MarketData {
public:
    explicit YahooMarketData(std::string baseUrl = "https://query1.finance.yahoo.com/v7/finance/quote",
                             std::chrono::milliseconds pollInterval = std::chrono::milliseconds(2000));
    ~YahooMarketData() override;

    void subscribe(const std::string& symbol) override;
    void unsubscribe(const std::string& symbol) override;
    void setQuoteCallback(QuoteCallback cb) override;
    void start() override;
    void stop() override;

private:
    void runLoop();
    void fetchAndPublish();

    std::string baseUrl_;
    std::chrono::milliseconds pollInterval_;
    std::atomic<bool> running_;
    std::thread worker_;
    std::mutex mtx_;
    std::condition_variable cv_;
    std::set<std::string> symbols_;
    QuoteCallback callback_;
};
