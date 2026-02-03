#include "IronCondorStrategy.hpp"
#include "core/MarketData.hpp"
#include "core/OrderManager.hpp"
#include "core/PositionManager.hpp"
#include "core/RiskManager.hpp"
#include "core/Logger.hpp"
#include "utils/ConfigLoader.hpp"
#include <algorithm>
#include <cmath>

IronCondorStrategy::IronCondorStrategy(MarketData& md, OrderManager& om, PositionManager& pm,
                                       RiskManager& rm, Logger& logger,
                                       std::shared_ptr<Pricer> pricer,
                                       std::shared_ptr<RoughVolModel> volModel)
    : marketData_(md), orderManager_(om), positionManager_(pm),
      riskManager_(rm), logger_(logger), pricer_(pricer), volModel_(volModel) {}

std::string IronCondorStrategy::name() const { return "IronCondorStrategy"; }

void IronCondorStrategy::initialize() {
    ConfigLoader cfg("config/strategy_config.json");
    if (cfg.load()) {
        if (cfg.has("underlying")) underlying_ = std::get<std::string>(cfg.get("underlying"));
        if (cfg.has("target_dte")) targetDte_ = std::get<int>(cfg.get("target_dte"));
        if (cfg.has("short_delta_target")) shortDeltaTarget_ = std::get<double>(cfg.get("short_delta_target"));
        if (cfg.has("width")) width_ = std::get<double>(cfg.get("width"));
        if (cfg.has("quantity")) quantity_ = std::get<int>(cfg.get("quantity"));
    }
    marketData_.subscribe(underlying_);
    logger_.info("IronCondorStrategy initialized");
}

double IronCondorStrategy::controlObjective(const std::vector<OptionContract>& legs,
                                            const StrategyContext& ctx) const {
    // Example: expected P&L minus risk penalty estimated by simulating IV surface paths
    // Use volModel_ to simulate surfaces and pricer_ to price legs; compute expected payoff.
    // Placeholder returns heuristic score: premium collected - 0.5 * estimated max loss
    double premium = 0.0;
    double estMaxLoss = 0.0;
    // compute using pricer_ and currentSurface_ (omitted for brevity)
    return premium - 0.5 * estMaxLoss;
}

void IronCondorStrategy::maybeOpenIronCondor(const StrategyContext& ctx) {
    // 1) find candidate strikes around shortDeltaTarget_ using currentSurface_
    // 2) build 4-leg iron condor OptionContract vector
    // 3) evaluate controlObjective for candidates
    // 4) validate via riskManager_.validateOrder for each leg
    // 5) send orders via orderManager_.sendOrder
    logger_.debug("Evaluating iron condor entry conditions (control-based)");
}

void IronCondorStrategy::manageOpenPositions(const StrategyContext& ctx) {
    // Monitor P&L, DTE, Greeks; if control objective deteriorates or risk thresholds breached,
    // close or adjust positions. Use riskManager_ to compute metrics.
    logger_.debug("Managing existing iron condor positions");
}

void IronCondorStrategy::onQuote(const Quote& quote, const StrategyContext& ctx) {
    if (quote.symbol != underlying_) return;
    // update spot in IV surface or mark-to-market
    maybeOpenIronCondor(ctx);
    manageOpenPositions(ctx);
}

void IronCondorStrategy::onTimer(const StrategyContext& ctx) {
    manageOpenPositions(ctx);
}
