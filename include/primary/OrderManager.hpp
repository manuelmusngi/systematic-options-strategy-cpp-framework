#ifndef ORDER_MANAGER_HPP
#define ORDER_MANAGER_HPP

#include "Option.hpp"
#include <vector>
#include <string>

class OrderManager {
public:
    void sendOrder(const Option& opt, int quantity, const std::string& side);
    void logOrders() const;

private:
    struct Order {
        Option option;
        int quantity;
        std::string side;
    };
    std::vector<Order> orders;
};

#endif // ORDER_MANAGER_HPP
