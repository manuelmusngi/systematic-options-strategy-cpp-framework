#include "models/IVSurface.hpp"
#include <stdexcept>

void IVSurface::setIV(Expiry expiry, double strike, double iv) {
    surface_[expiry][strike] = iv;
}

double IVSurface::getIV(Expiry expiry, double strike) const {
    auto it = surface_.find(expiry);
    if (it == surface_.end()) throw std::runtime_error("expiry not found");
    auto it2 = it->second.lower_bound(strike);
    if (it2 == it->second.end()) {
        // fallback to last
        return it->second.rbegin()->second;
    }
    return it2->second;
}

std::vector<IVSurface::Expiry> IVSurface::expiries() const {
    std::vector<Expiry> out;
    for (auto &p : surface_) out.push_back(p.first);
    return out;
}

std::vector<double> IVSurface::strikesForExpiry(Expiry expiry) const {
    std::vector<double> out;
    auto it = surface_.find(expiry);
    if (it == surface_.end()) return out;
    for (auto &p : it->second) out.push_back(p.first);
    return out;
}
