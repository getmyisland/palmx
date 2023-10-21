#include <palmx_debug.h>

#include <chrono>
#include <filesystem>
#include <iostream>
#include <source_location>

namespace palmx
{
    std::string GetCurrentTime()
    {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::string time_str = std::ctime(&time);
        time_str.pop_back();

        return time_str;
    }

    std::string GetLocationString(std::source_location const source)
    {
        return "[" + std::filesystem::path(source.file_name()).filename().string() + "] [" + source.function_name() + "] [" + std::to_string(source.line()) + ":" + std::to_string(source.column()) + "]";
    }

    void LogInfo(std::string const message, std::source_location const source)
    {
        std::cout << GetCurrentTime() << " [INFO] " << GetLocationString(source) << " " << message << "\n";
    }

    void LogWarning(std::string const message, std::source_location const source)
    {
        std::cout << GetCurrentTime() << " [WARNING] " << GetLocationString(source) << " " << message << "\n";
    }

    void LogError(std::string const message, std::source_location const source)
    {
        std::cout << GetCurrentTime() << " [ERROR] " << GetLocationString(source) << " " << message << "\n";
    }
}