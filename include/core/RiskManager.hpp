#pragma once
#include <string>

class PositionManager;
class Order;

struct RiskMetrics {
    double estimatedMaxLoss{};
    double marginRequired{};
    double portfolioDelta{};
};

class RiskManager {
public:
    virtual ~RiskManager() = default;
    virtual bool validateOrder(const Order& order, const PositionManager& positions) const = 0;
    virtual RiskMetrics currentPortfolioRisk(const PositionManager& positions) const = 0;
    virtual void setTransactionCostPerContract(double cost) = 0;
};
