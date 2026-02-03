#pragma once
#include <string>
#include <chrono>

enum class OptionType { Call, Put };

struct OptionContract {
    std::string underlying;
    double strike{};
    std::chrono::system_clock::time_point expiry{};
    OptionType type{};
    std::string symbol; // broker symbol
};
