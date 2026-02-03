#include "pricing/Pricer.hpp"
#include "../utils/MathUtils.hpp"
#include <cmath>

class BlackScholesPricer : public Pricer {
public:
    double price(const OptionContract& opt, double spot,
                 const IVSurface& ivSurface, double rate,
                 std::chrono::system_clock::time_point valuationTime) const override {
        // simple interpolation: get IV for expiry and strike
        double iv = ivSurface.getIV(opt.expiry, opt.strike);
        using namespace std::chrono;
        double T = duration_cast<duration<double>>(opt.expiry - valuationTime).count() / (365.0*24*3600);
        if (T <= 0) {
            if (opt.type == OptionType::Call) return std::max(spot - opt.strike, 0.0);
            return std::max(opt.strike - spot, 0.0);
        }
        double sigma = iv;
        double sqrtT = std::sqrt(T);
        double d1 = (std::log(spot / opt.strike) + (rate + 0.5 * sigma * sigma) * T) / (sigma * sqrtT);
        double d2 = d1 - sigma * sqrtT;
        if (opt.type == OptionType::Call) {
            return spot * MathUtils::normalCdf(d1) - opt.strike * std::exp(-rate * T) * MathUtils::normalCdf(d2);
        } else {
            return opt.strike * std::exp(-rate * T) * MathUtils::normalCdf(-d2) - spot * MathUtils::normalCdf(-d1);
        }
    }

    Greeks greeks(const OptionContract& opt, double spot,
                  const IVSurface& ivSurface, double rate,
                  std::chrono::system_clock::time_point valuationTime) const override {
        // finite-difference or analytic formulas; placeholder returns approximate delta
        double price0 = price(opt, spot, ivSurface, rate, valuationTime);
        OptionContract optUp = opt;
        double eps = 1e-4 * spot;
        double priceUp = price(optUp, spot + eps, ivSurface, rate, valuationTime);
        Greeks g;
        g.delta = (priceUp - price0) / eps;
        return g;
    }
};
