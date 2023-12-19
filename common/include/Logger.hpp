#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>
#include <sstream>

#include "LogLevel.hpp"

class Logger {
public:
    static Logger& getInstance();

    template <typename... Args>
    void log(LogLevel level, const std::string& format, Args... args);

private:
    Logger() = default;

    void logWithColor(const std::string& message, const std::string& color);

    static const std::string getColor(LogLevel level);
    static const std::string getLogLevelString(LogLevel level);
};

template <typename... Args>
void Logger::log(LogLevel level, const std::string& format, Args... args) {
    std::ostringstream oss;
    printWithFormat(oss, format, args...);

    std::string color = getColor(level);
    std::string logLevelString = getLogLevelString(level);
    
    logWithColor("[" + logLevelString + "] " + oss.str(), color);
}

template <typename T>
void printWithFormat(std::ostringstream& oss, const T& value) {
    oss << value;
}

template <typename T, typename... Args>
void printWithFormat(std::ostringstream& oss, const T& value, Args... args) {
    oss << value;
    printWithFormat(oss, args...);
}


#endif
