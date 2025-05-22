#include "../../include/core/OrderManager.hpp"
#include <iostream>

void OrderManager::sendOrder(const Option& opt, int quantity, const std::string& side) {
    orders.push_back({opt, quantity, side});
    std::cout << "Order: " << side << " " << quantity << " " << opt.symbol << "@" << MathUtils::midPrice(opt.bid, opt.ask) << std::endl;
}

void OrderManager::logOrders() const {
    for (const auto& order : orders) {
        std::cout << order.side << " " << order.quantity << " " << order.option.symbol << std::endl;
    }
}

// src/core/PositionManager.cpp
#include "../../include/core/PositionManager.hpp"

void PositionManager::updatePosition(const Option& opt, int quantity) {
    positions[opt.symbol] += quantity;
}

int PositionManager::getPosition(const std::string& symbol) const {
    auto it = positions.find(symbol);
    return it != positions.end() ? it->second : 0;
}
