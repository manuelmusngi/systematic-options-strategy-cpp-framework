#include "../../include/core/MarketData.hpp"
#include <iostream>

MarketData::MarketData(const std::string& filepath) {
    loadFromCSV(filepath);
}

void MarketData::loadFromCSV(const std::string& filepath) {
    std::ifstream file(filepath);
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Option opt;
        std::string type;
        std::getline(ss, opt.symbol, ',');
        ss >> opt.strike; ss.ignore();
        std::getline(ss, opt.expiry, ',');
        ss >> opt.bid; ss.ignore();
        ss >> opt.ask; ss.ignore();
        ss >> type; opt.type = type[0];
        ss >> opt.greeks.delta >> opt.greeks.gamma >> opt.greeks.theta >> opt.greeks.vega;
        dataQueue.push(opt);
    }
}

bool MarketData::hasNext() const {
    return !dataQueue.empty();
}

Option MarketData::next() {
    Option opt = dataQueue.front();
    dataQueue.pop();
    return opt;
}
