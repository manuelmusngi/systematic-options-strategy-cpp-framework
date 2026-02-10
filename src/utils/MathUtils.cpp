#include "utils/MathUtils.hpp"

namespace MathUtils {

double normalPdf(double x) {
    static constexpr double invSqrt2Pi = 0.3989422804014327;
    return invSqrt2Pi * std::exp(-0.5 * x * x);
}

double normalCdf(double x) {
    return 0.5 * std::erfc(-x / std::sqrt(2.0));
}

double blackScholesPrice(double spot, double strike, double rate,
                         double vol, double timeToExpiry, bool isCall) {
    if (timeToExpiry <= 0 || vol <= 0) {
        const double intrinsic = isCall ? std::max(spot - strike, 0.0)
                                        : std::max(strike - spot, 0.0);
        return intrinsic;
    }

    const double sqrtT = std::sqrt(timeToExpiry);
    const double d1 = (std::log(spot / strike) + (rate + 0.5 * vol * vol) * timeToExpiry) / (vol * sqrtT);
    const double d2 = d1 - vol * sqrtT;

    if (isCall) {
        return spot * normalCdf(d1) - strike * std::exp(-rate * timeToExpiry) * normalCdf(d2);
    } else {
        return strike * std::exp(-rate * timeToExpiry) * normalCdf(-d2) - spot * normalCdf(-d1);
    }
}

}
