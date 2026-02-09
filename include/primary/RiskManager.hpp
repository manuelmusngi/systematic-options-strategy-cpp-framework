#pragma once
#include <string>

class PositionManager;
class Order;

class RiskManager {
public:
    virtual ~RiskManager() = default;

    virtual bool validateOrder(const Order& order, const PositionManager& positions) const = 0;
    virtual double currentPortfolioRisk(const PositionManager& positions) const = 0;
};
