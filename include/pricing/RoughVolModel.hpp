#pragma once
#include "../models/IVSurface.hpp"
#include <chrono>

// Minimal interface for a rough/multifactor vol model used for simulation/calibration.
class RoughVolModel {
public:
    virtual ~RoughVolModel() = default;
    virtual void calibrate(const IVSurface& marketSurface) = 0;
    virtual IVSurface simulateSurface(std::chrono::system_clock::time_point t0,
                                      int steps,
                                      std::chrono::seconds dt) const = 0;
};
