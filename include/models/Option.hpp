#ifndef OPTION_HPP
#define OPTION_HPP

#include <string>
#include "Greeks.hpp"

struct Option {
    std::string symbol;
    double strike;
    std::string expiry;
    double bid;
    double ask;
    char type; // 'C' or 'P'
    Greeks greeks;
};

#endif // OPTION_HPP
