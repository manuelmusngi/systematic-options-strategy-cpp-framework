#ifndef POSITION_MANAGER_HPP
#define POSITION_MANAGER_HPP

#include <unordered_map>
#include "Option.hpp"

class PositionManager {
public:
    void updatePosition(const Option& opt, int quantity);
    int getPosition(const std::string& symbol) const;

private:
    std::unordered_map<std::string, int> positions;
};

#endif // POSITION_MANAGER_HPP
