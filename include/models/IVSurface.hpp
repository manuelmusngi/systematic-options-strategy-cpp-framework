#pragma once
#include <vector>
#include <chrono>
#include <map>

// Simple grid-based IV surface: expiry -> strike -> iv
class IVSurface {
public:
    using Expiry = std::chrono::system_clock::time_point;
    void setIV(Expiry expiry, double strike, double iv);
    double getIV(Expiry expiry, double strike) const;
    std::vector<Expiry> expiries() const;
    std::vector<double> strikesForExpiry(Expiry expiry) const;
private:
    std::map<Expiry, std::map<double, double>> surface_;
};
