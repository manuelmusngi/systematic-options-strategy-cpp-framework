#pragma once
#include <string>
#include <functional>
#include <chrono>
#include <vector>
#include <memory>

struct Quote {
    std::string symbol;
    double bid{};
    double ask{};
    double last{};
    std::chrono::system_clock::time_point timestamp{};
};

class MarketData {
public:
    using QuoteCallback = std::function<void(const Quote&)>;
    virtual ~MarketData() = default;
    virtual void subscribe(const std::string& symbol) = 0;
    virtual void unsubscribe(const std::string& symbol) = 0;
    virtual void setQuoteCallback(QuoteCallback cb) = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
};
