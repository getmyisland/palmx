#include "LogManager.h"

#include <date/date.h>

#include <chrono>
#include <filesystem>
#include <iostream>
#include <source_location>

namespace palmx
{
    LogManager::LogManager() {}
    LogManager::~LogManager() {}

    template<> LogManager* Singleton<LogManager>::msSingleton = 0;
    LogManager* LogManager::GetSingletonPtr(void)
    {
        return msSingleton;
    }
    LogManager& LogManager::GetSingleton(void)
    {
        return (*msSingleton);
    }
    
    void LogManager::StartUp()
    {
        DEBUG_LOG_INFO("Log Manager initialized");
    }

    void LogManager::ShutDown()
    {

    }
    
    std::string GetLocationString(std::source_location const source)
    {
        return "[" + std::filesystem::path(source.file_name()).filename().string() + "] [" + source.function_name() + "] [" + std::to_string(source.line()) + ":" + std::to_string(source.column()) + "]";
    }

    void LogManager::LogInfo(std::string const message, std::source_location const source)
    {
        using namespace date;
        std::cout << std::chrono::system_clock::now() << " [INFO] " << GetLocationString(source) << " " << message << "\n";
    }

    void LogManager::LogWarning(std::string const message, std::source_location const source)
    {
        using namespace date;
        std::cout << std::chrono::system_clock::now() << " [WARNING] " << GetLocationString(source) << " " << message << "\n";
    }

    void LogManager::LogError(std::string const message, std::source_location const source)
    {
        using namespace date;
        std::cout << std::chrono::system_clock::now() << " [ERROR] " << GetLocationString(source) << " " << message << "\n";
    }
}