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

std::wstring GetLocationStringW(std::source_location const source)
{
	const char* function_name = source.function_name();
	size_t wlength = strlen(function_name);

	wchar_t wfunction_name[30];
	mbstowcs_s(&wlength, wfunction_name, function_name, wlength);

	return L"[" + std::filesystem::path(source.file_name()).filename().wstring() + L"] [" + wfunction_name + L"] [" + std::to_wstring(source.line()) + L":" + std::to_wstring(source.column()) + L"]";
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

void Logger::LogLastError(Logger::Severity const severity, DWORD const errorMessageID, std::source_location const source)
{
	if (errorMessageID == 0) {
		return; //No error message has been recorded
	}

	LPSTR messageBuffer = nullptr;

	//Ask Win32 to give us the string version of that message ID.
	//The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

	//Copy the error message into a std::string.
	std::string message(messageBuffer, size);

	//Free the Win32's string's buffer.
	LocalFree(messageBuffer);
	
	using namespace date;
	std::cout << std::chrono::system_clock::now() << " [" << GetSeverityLevel(severity) << "] " << GetLocationString(source) << " " << message << std::endl;
}
