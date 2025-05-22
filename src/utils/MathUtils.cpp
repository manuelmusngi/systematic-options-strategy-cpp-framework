#include "../../include/utils/MathUtils.hpp"

namespace MathUtils {
    double midPrice(double bid, double ask) {
        return (bid + ask) / 2.0;
    }
}
