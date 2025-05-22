#ifndef RISK_MANAGER_HPP
#define RISK_MANAGER_HPP

class RiskManager {
public:
    bool checkRisk(double deltaExposure);
private:
    const double MAX_DELTA = 100.0;
};

#endif // RISK_MANAGER_HPP
