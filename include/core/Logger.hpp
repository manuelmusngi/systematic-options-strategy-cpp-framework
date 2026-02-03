#pragma once
#include <string_view>

enum class LogLevel { Debug, Info, Warn, Error };

class Logger {
public:
    virtual ~Logger() = default;
    virtual void log(LogLevel level, std::string_view msg) = 0;
    void info(std::string_view msg) { log(LogLevel::Info, msg); }
    void debug(std::string_view msg) { log(LogLevel::Debug, msg); }
    void warn(std::string_view msg) { log(LogLevel::Warn, msg); }
    void error(std::string_view msg) { log(LogLevel::Error, msg); }
};
