#include "logger.h"

#include <date/date.h>

#include <chrono>
#include <filesystem>
#include <iostream>
#include <source_location>

namespace palmx
{
    Logger::Logger() {}
    Logger::~Logger() {}
    
    std::string GetLocationString(std::source_location const source)
    {
        return "[" + std::filesystem::path(source.file_name()).filename().string() + "] [" + source.function_name() + "] [" + std::to_string(source.line()) + ":" + std::to_string(source.column()) + "]";
    }

    void Logger::LogInfo(std::string const message, std::source_location const source)
    {
        using namespace date;
        std::cout << std::chrono::system_clock::now() << " [INFO] " << GetLocationString(source) << " " << message << "\n";
    }

    void Logger::LogWarning(std::string const message, std::source_location const source)
    {
        using namespace date;
        std::cout << std::chrono::system_clock::now() << " [WARNING] " << GetLocationString(source) << " " << message << "\n";
    }

    void Logger::LogError(std::string const message, std::source_location const source)
    {
        using namespace date;
        std::cout << std::chrono::system_clock::now() << " [ERROR] " << GetLocationString(source) << " " << message << "\n";
    }
}