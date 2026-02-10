#include "primary/Logger.hpp"
#include <iostream>

class StdoutLogger : public Logger {
public:
    void log(LogLevel level, std::string_view msg) override {
        std::string prefix;
        switch (level) {
            case LogLevel::Debug: prefix = "[DEBUG] "; break;
            case LogLevel::Info:  prefix = "[INFO ] "; break;
            case LogLevel::Warn:  prefix = "[WARN ] "; break;
            case LogLevel::Error: prefix = "[ERROR] "; break;
        }
        std::cout << prefix << msg << '\n';
    }
};
