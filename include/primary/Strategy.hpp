#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include "Option.hpp"

class Strategy {
public:
    virtual void onMarketData(const Option& opt) = 0;
    virtual void evaluate() = 0;
    virtual ~Strategy() = default;
};

#endif // STRATEGY_HPP
