#include "utils/ConfigLoader.hpp"
#include <fstream>
#include <nlohmann/json.hpp> // or replace with your own JSON parser

ConfigLoader::ConfigLoader(std::string path)
    : path_(std::move(path)) {}

bool ConfigLoader::load() {
    std::ifstream in(path_);
    if (!in) return false;

    nlohmann::json j;
    in >> j;

    values_.clear();
    for (auto it = j.begin(); it != j.end(); ++it) {
        if (it->is_string()) values_[it.key()] = it->get<std::string>();
        else if (it->is_number_integer()) values_[it.key()] = it->get<int>();
        else if (it->is_number_float()) values_[it.key()] = it->get<double>();
        else if (it->is_boolean()) values_[it.key()] = it->get<bool>();
    }
    return true;
}

ConfigValue ConfigLoader::get(const std::string& key) const {
    return values_.at(key);
}

bool ConfigLoader::has(const std::string& key) const {
    return values_.find(key) != values_.end();
}
