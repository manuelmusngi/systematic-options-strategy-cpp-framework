int main() {
    MarketData md("data/options_data.csv");
    std::unique_ptr<Strategy> strat = std::make_unique<IronCondorStrategy>();

    while (md.hasNext()) {
        Option opt = md.next();
        strat->onMarketData(opt);
        strat->evaluate();
    }

    return 0;
}
