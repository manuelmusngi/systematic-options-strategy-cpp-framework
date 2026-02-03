#pragma once
#include <string>
#include <memory>
#include <chrono>

struct StrategyContext {
    std::chrono::system_clock::time_point now;
};

class MarketData;
class OrderManager;
class PositionManager;
class RiskManager;
class Logger;

class Strategy {
public:
    virtual ~Strategy() = default;
    virtual std::string name() const = 0;
    virtual void initialize() = 0;
    virtual void onQuote(const Quote& quote, const StrategyContext& ctx) = 0;
    virtual void onTimer(const StrategyContext& ctx) = 0;
};
