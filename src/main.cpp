#include "../include/core/MarketData.hpp"
#include "../include/core/OrderManager.hpp"
#include "../include/core/PositionManager.hpp"
#include "../include/core/RiskManager.hpp"
#include "../include/core/Logger.hpp"
#include "../strategies/IronCondorStrategy.hpp"
#include <memory>

int main() {
    MarketData marketData("data/options_data.csv");
    OrderManager orderManager;
    PositionManager positionManager;
    RiskManager riskManager;

    std::unique_ptr<Strategy> strategy = std::make_unique<IronCondorStrategy>(orderManager, positionManager, riskManager);

    while (marketData.hasNext()) {
        Option opt = marketData.next();
        strategy->onMarketData(opt);
    }

    strategy->evaluate();
    orderManager.logOrders();
    return 0;
}
