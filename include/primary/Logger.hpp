#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>

class Logger {
public:
    static void log(const std::string& message);

private:
    static std::mutex logMutex;
};

#endif // LOGGER_HPP
