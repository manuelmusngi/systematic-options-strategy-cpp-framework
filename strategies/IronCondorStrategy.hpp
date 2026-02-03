#pragma once
#include "core/Strategy.hpp"
#include "models/Option.hpp"
#include "pricing/Pricer.hpp"
#include "models/IVSurface.hpp"
#include <memory>

class IronCondorStrategy : public Strategy {
public:
    IronCondorStrategy(MarketData& md,
                       OrderManager& om,
                       PositionManager& pm,
                       RiskManager& rm,
                       Logger& logger,
                       std::shared_ptr<Pricer> pricer,
                       std::shared_ptr<RoughVolModel> volModel);

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
    std::shared_ptr<Pricer> pricer_;
    std::shared_ptr<RoughVolModel> volModel_;

    std::string underlying_;
    int targetDte_;
    double shortDeltaTarget_;
    double width_;
    int quantity_;

    IVSurface currentSurface_;

    // control objective: returns expected utility / reward for candidate legs
    double controlObjective(const std::vector<OptionContract>& legs,
                            const StrategyContext& ctx) const;

    void maybeOpenIronCondor(const StrategyContext& ctx);
    void manageOpenPositions(const StrategyContext& ctx);
};
