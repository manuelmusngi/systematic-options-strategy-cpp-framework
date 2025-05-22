#include "../../include/utils/ConfigLoader.hpp"
#include <fstream>
#include <sstream>

bool ConfigLoader::loadConfig(const std::string& filepath) {
    std::ifstream file(filepath);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string key, value;
        if (std::getline(ss, key, '=') && std::getline(ss, value)) {
            configMap[key] = value;
        }
    }
    return true;
}

std::string ConfigLoader::getValue(const std::string& key) const {
    auto it = configMap.find(key);
    return it != configMap.end() ? it->second : "";
}
