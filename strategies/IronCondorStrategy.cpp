#include "IronCondorStrategy.hpp"
#include "primary/MarketData.hpp"
#include "primary/OrderManager.hpp"
#include "primary/PositionManager.hpp"
#include "primary/RiskManager.hpp"
#include "primary/Logger.hpp"
#include "utils/ConfigLoader.hpp"

IronCondorStrategy::IronCondorStrategy(MarketData& md,
                                       OrderManager& om,
                                       PositionManager& pm,
                                       RiskManager& rm,
                                       Logger& logger)
    : marketData_(md)
    , orderManager_(om)
    , positionManager_(pm)
    , riskManager_(rm)
    , logger_(logger) {}

std::string IronCondorStrategy::name() const {
    return "IronCondorStrategy";
}

void IronCondorStrategy::initialize() {
    // Load config (path could be injected instead)
    ConfigLoader loader{"config/strategy_config.json"};
    if (loader.load()) {
        if (loader.has("underlying")) underlying_ = std::get<std::string>(loader.get("underlying"));
        if (loader.has("target_dte")) targetDte_ = std::get<int>(loader.get("target_dte"));
        if (loader.has("short_delta_target")) shortDeltaTarget_ = std::get<double>(loader.get("short_delta_target"));
        if (loader.has("width")) width_ = std::get<double>(loader.get("width"));
        if (loader.has("quantity")) quantity_ = std::get<int>(loader.get("quantity"));
    }
    logger_.info("IronCondorStrategy initialized");
    marketData_.subscribe(underlying_);
}

void IronCondorStrategy::onQuote(const Quote& quote, const StrategyContext& ctx) {
    if (quote.symbol != underlying_) return;
    maybeOpenIronCondor(ctx);
    manageOpenPositions(ctx);
}

void IronCondorStrategy::onTimer(const StrategyContext& ctx) {
    manageOpenPositions(ctx);
}

void IronCondorStrategy::maybeOpenIronCondor(const StrategyContext& ctx) {
    // Placeholder: determine strikes around shortDeltaTarget_, construct 4-leg iron condor,
    // validate via RiskManager, then send orders via OrderManager.
    logger_.debug("Evaluating iron condor entry conditions");
}

void IronCondorStrategy::manageOpenPositions(const StrategyContext& ctx) {
    // Placeholder: monitor P&L, DTE, and risk; adjust or close positions.
    logger_.debug("Managing existing iron condor positions");
}
