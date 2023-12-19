
#include "Logger.hpp"

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

const std::string Logger::getColor(LogLevel level) {
    switch (level) {
        case LogLevel::DEBUG:
            return "\033[36m";
        case LogLevel::INFO:
            return "\033[32m"; 
        case LogLevel::WARNING:
            return "\033[33m";
        case LogLevel::ERROR:
            return "\033[31m";
        default:
            return "\033[0m"; 
    }
}

const std::string Logger::getLogLevelString(LogLevel level) {
    switch (level) {
        case LogLevel::DEBUG:
            return "DEBUG";
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::WARNING:
            return "WARNING";
        case LogLevel::ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
}

void Logger::logWithColor(const std::string& message, const std::string& color) {
    std::cout << color << message << "\033[0m" << std::endl;
}
