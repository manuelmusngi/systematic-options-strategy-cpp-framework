#pragma once
#include "Strategy.hpp"
#include "Option.hpp"
#include "Greeks.hpp"
#include <vector>

class IronCondorStrategy : public Strategy {
public:
    IronCondorStrategy(MarketData& md,
                       OrderManager& om,
                       PositionManager& pm,
                       RiskManager& rm,
                       Logger& logger);

    std::string name() const override;
    void initialize() override;
    void onQuote(const Quote& quote, const StrategyContext& ctx) override;
    void onTimer(const StrategyContext& ctx) override;

private:
    MarketData& marketData_;
    OrderManager& orderManager_;
    PositionManager& positionManager_;
    RiskManager& riskManager_;
    Logger& logger_;

    std::string underlying_;
    int targetDte_{};
    double shortDeltaTarget_{};
    double width_{};
    int quantity_{};

    void maybeOpenIronCondor(const StrategyContext& ctx);
    void manageOpenPositions(const StrategyContext& ctx);
};
