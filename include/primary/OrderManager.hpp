#pragma once
#include <string>
#include <chrono>
#include <optional>
#include <vector>

enum class OrderSide { Buy, Sell };
enum class OrderType { Market, Limit };
enum class OrderStatus { New, PartiallyFilled, Filled, Cancelled, Rejected };

struct Order {
    std::string id;
    std::string symbol;
    OrderSide side;
    OrderType type;
    int quantity{};
    double price{};
    std::chrono::system_clock::time_point timestamp{};
};

struct ExecutionReport {
    std::string orderId;
    OrderStatus status;
    int filledQuantity{};
    double avgPrice{};
    std::chrono::system_clock::time_point timestamp{};
};

class OrderManager {
public:
    virtual ~OrderManager() = default;

    virtual std::string sendOrder(const Order& order) = 0;
    virtual void cancelOrder(const std::string& orderId) = 0;
    virtual std::optional<Order> getOrder(const std::string& orderId) const = 0;
    virtual std::vector<Order> getOpenOrders() const = 0;
};
