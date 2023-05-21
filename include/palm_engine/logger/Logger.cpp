#include <date/date.h>
#include "Logger.h"
#include <source_location>
#include <iostream>
#include <chrono>
#include <filesystem>

std::string GetLocationString(std::source_location const source)
{
    return "[" + std::filesystem::path(source.file_name()).filename().string() + "] [" + source.function_name() + "] [" + std::to_string(source.line()) + ":" + std::to_string(source.column()) + "]";
}

std::string GetSeverityLevel(PalmEngine::Logger::Severity severity)
{
	switch (severity)
	{
	case PalmEngine::Logger::Severity::Debug:
	{
		return "DEBUG";
	}
	case PalmEngine::Logger::Severity::Info:
	{
		return "INFO";
	}
	case PalmEngine::Logger::Severity::Warning:
	{
		return "WARNING";
	}
	case PalmEngine::Logger::Severity::Error:
	{
		return "ERROR";
	}
	default:
		return "";
	}
}

void PalmEngine::Logger::Log(Logger::Severity const severity, std::string const message, std::source_location const source)
{
    using namespace date;
    std::cout << std::chrono::system_clock::now() << " [" << GetSeverityLevel(severity) << "] " << GetLocationString(source) << " " << message << std::endl;
}