#ifndef MARKET_DATA_HPP
#define MARKET_DATA_HPP

#include <string>
#include <queue>
#include <fstream>
#include <sstream>
#include <vector>
#include "Option.hpp"

class MarketData {
public:
    MarketData(const std::string& filepath);
    bool hasNext() const;
    Option next();

private:
    std::queue<Option> dataQueue;
    void loadFromCSV(const std::string& filepath);
};

#endif // MARKET_DATA_HPP
