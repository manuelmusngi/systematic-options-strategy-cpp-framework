#include "../../include/core/RiskManager.hpp"

bool RiskManager::checkRisk(double deltaExposure) {
    return std::abs(deltaExposure) <= MAX_DELTA;
}
