#include "primary/PositionManager.hpp"
#include <unordered_map>

class BasicPositionManager : public PositionManager {
public:
    void onExecution(const std::string& symbol, int fillQty, double fillPrice) override {
        auto& pos = positions_[symbol];
        pos.symbol = symbol;
        const int newQty = pos.quantity + fillQty;
        if (newQty == 0) {
            pos.quantity = 0;
            pos.avgPrice = 0.0;
            return;
        }
        const double totalCost = pos.avgPrice * pos.quantity + fillQty * fillPrice;
        pos.quantity = newQty;
        pos.avgPrice = totalCost / newQty;
    }

    Position getPosition(const std::string& symbol) const override {
        auto it = positions_.find(symbol);
        if (it != positions_.end()) return it->second;
        return Position{symbol, 0, 0.0};
    }

    double getNetExposure() const override {
        double exposure = 0.0;
        for (const auto& [_, pos] : positions_) {
            exposure += pos.quantity * pos.avgPrice;
        }
        return exposure;
    }

private:
    std::unordered_map<std::string, Position> positions_;
};
