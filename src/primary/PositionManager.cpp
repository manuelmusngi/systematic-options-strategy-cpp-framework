#include "../../include/primary/PositionManager.hpp"

void PositionManager::updatePosition(const Option& opt, int quantity) {
    positions[opt.symbol] += quantity;
}

int PositionManager::getPosition(const std::string& symbol) const {
    auto it = positions.find(symbol);
    return it != positions.end() ? it->second : 0;
}
