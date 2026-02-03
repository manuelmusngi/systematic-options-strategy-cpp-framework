#pragma once
#include <string>
#include <unordered_map>
#include <variant>

using ConfigValue = std::variant<std::string, int, double, bool>;

class ConfigLoader {
public:
    explicit ConfigLoader(std::string path);
    bool load();
    ConfigValue get(const std::string& key) const;
    bool has(const std::string& key) const;
private:
    std::string path_;
    std::unordered_map<std::string, ConfigValue> values_;
};
