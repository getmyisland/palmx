#ifndef LOGGER_H
#define LOGGER_H
#ifdef _WIN32
#pragma once
#endif

#define LOGGER Logger::GetInstance()

#include <string>
#include <source_location>

class Logger
{
public:
	enum class Severity
	{
		Debug,
		Info,
		Warning,
		Error
	};

	static Logger& GetInstance() {
		static Logger instance;

		return instance;
	}

	Logger(Logger const&) = delete;
	void operator=(Logger const&) = delete;

private:
	Logger() {}

public:
	void Log(Logger::Severity const severity,
		std::string const message,
		std::source_location const source = std::source_location::current());

	void LogW(Logger::Severity const severity,
		std::wstring const message,
		std::source_location const source = std::source_location::current());
};

#endif // LOGGER_H