#include <date/date.h>
#include "LogManager.h"
#include <source_location>
#include <iostream>
#include <chrono>
#include <filesystem>

namespace PalmEngine
{
    LogManager::LogManager() {}
    LogManager::~LogManager() {}

    template<> LogManager* PalmEngineSingleton<LogManager>::ms_Singleton = 0;
    LogManager* LogManager::GetSingletonPtr(void)
    {
        return ms_Singleton;
    }
    LogManager& LogManager::GetSingleton(void)
    {
        return (*ms_Singleton);
    }
    
    void LogManager::StartUp()
    {
        PE_LOG_MANAGER->LogInfo("Log Manager initialized");
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