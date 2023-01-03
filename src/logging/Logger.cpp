#include "Logger.h"
#include <source_location>
#include <iostream>
#include <chrono>
#include <filesystem>
#include <date/date.h>

std::string GetLocationString(std::source_location const source)
{
    return "[" + std::filesystem::path(source.file_name()).filename().string() + "] [" + source.function_name() + "@" + std::to_string(source.line()) + "]";
}

std::wstring GetLocationStringW(std::source_location const source)
{
	const char* function_name = source.function_name();
	size_t wlength = strlen(function_name);

	wchar_t wfunction_name[30];
	mbstowcs_s(&wlength, wfunction_name, function_name, wlength);

	return L"[" + std::filesystem::path(source.file_name()).filename().wstring() + L"] [" + wfunction_name + L"@" + std::to_wstring(source.line()) + L"]";
}

std::string GetSeverityLevel(Logger::Severity p_Severity)
{
	switch (p_Severity)
	{
	case Logger::Severity::Debug:
	{
		return "DEBUG";
	}
	case Logger::Severity::Info:
	{
		return "INFO";
	}
	case Logger::Severity::Warning:
	{
		return "WARNING";
	}
	case Logger::Severity::Error:
	{
		return "ERROR";
	}
	default:
		return "";
	}
}

std::wstring GetSeverityLevelW(Logger::Severity p_Severity)
{
	switch (p_Severity)
	{
	case Logger::Severity::Debug:
	{
		return L"DEBUG";
	}
	case Logger::Severity::Info:
	{
		return L"INFO";
	}
	case Logger::Severity::Warning:
	{
		return L"WARNING";
	}
	case Logger::Severity::Error:
	{
		return L"ERROR";
	}
	default:
		return L"";
	}
}

void Logger::Log(Logger::Severity const severity, std::string const message, std::source_location const source)
{
    using namespace date;
    std::cout << std::chrono::system_clock::now() << " [" << GetSeverityLevel(severity) << "] " << GetLocationString(source) << " " << message << std::endl;
}

void Logger::LogW(Logger::Severity const severity, std::wstring const message, std::source_location const source)
{
	using namespace date;
	std::wcout << std::chrono::system_clock::now() << L" [" << GetSeverityLevelW(severity) << L"] " << GetLocationStringW(source) << L" " << message << std::endl;
}