#include <palmx/logger.h>

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

    void Logger::Info(std::string const message, std::source_location const source)
    {
        std::cout << std::chrono::system_clock::now() << " [INFO] " << GetLocationString(source) << " " << message << "\n";
    }

    void Logger::Warning(std::string const message, std::source_location const source)
    {
        std::cout << std::chrono::system_clock::now() << " [WARNING] " << GetLocationString(source) << " " << message << "\n";
    }

    void Logger::Error(std::string const message, std::source_location const source)
    {
        std::cout << std::chrono::system_clock::now() << " [ERROR] " << GetLocationString(source) << " " << message << "\n";
    }
}