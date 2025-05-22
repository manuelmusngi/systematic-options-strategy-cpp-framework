#ifndef CONFIG_LOADER_HPP
#define CONFIG_LOADER_HPP

#include <string>
#include <unordered_map>

class ConfigLoader {
public:
    bool loadConfig(const std::string& filepath);
    std::string getValue(const std::string& key) const;

private:
    std::unordered_map<std::string, std::string> configMap;
};

#endif // CONFIG_LOADER_HPP
