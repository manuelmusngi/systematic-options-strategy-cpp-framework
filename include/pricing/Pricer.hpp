#pragma once
#include "../models/Option.hpp"
#include "../models/IVSurface.hpp"
#include "../models/Greeks.hpp"
#include <chrono>

class Pricer {
public:
    virtual ~Pricer() = default;
    virtual double price(const OptionContract& opt, double spot,
                         const IVSurface& ivSurface,
                         double rate,
                         std::chrono::system_clock::time_point valuationTime) const = 0;
    virtual Greeks greeks(const OptionContract& opt, double spot,
                          const IVSurface& ivSurface,
                          double rate,
                          std::chrono::system_clock::time_point valuationTime) const = 0;
};
