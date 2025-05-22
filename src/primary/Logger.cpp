#include "../../include/core/Logger.hpp"
#include <mutex>

std::mutex Logger::logMutex;

void Logger::log(const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);
    std::cout << message << std::endl;
}
