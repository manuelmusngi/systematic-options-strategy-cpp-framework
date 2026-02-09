#pragma once
#include <string>
#include <unordered_map>

struct Position {
    std::string symbol;
    int quantity{};
    double avgPrice{};
};

class PositionManager {
public:
    virtual ~PositionManager() = default;

    virtual void onExecution(const std::string& symbol, int fillQty, double fillPrice) = 0;
    virtual Position getPosition(const std::string& symbol) const = 0;
    virtual double getNetExposure() const = 0;
};
