#include "core/RiskManager.hpp"
#include "core/PositionManager.hpp"
#include <cmath>

class SimpleRiskManager : public RiskManager {
public:
    SimpleRiskManager() : txCostPerContract_(0.0) {}
    bool validateOrder(const Order& order, const PositionManager& positions) const override {
        // Example rules: max contracts, margin check, and transaction cost penalty
        if (std::abs(order.quantity) > 1000) return false;
        // margin and portfolio risk checks would go here
        return true;
    }
    RiskMetrics currentPortfolioRisk(const PositionManager& positions) const override {
        RiskMetrics m;
        m.estimatedMaxLoss = std::abs(positions.getNetExposure()) * 0.1;
        m.marginRequired = std::abs(positions.getNetExposure()) * 0.2;
        return m;
    }
    void setTransactionCostPerContract(double cost) override { txCostPerContract_ = cost; }
private:
    double txCostPerContract_;
};
