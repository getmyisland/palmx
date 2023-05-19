#ifndef LOGGER_H
#define LOGGER_H

#define SEVERITY_DEBUG Logger::Severity::Debug
#define SEVERITY_INFO Logger::Severity::Info
#define SEVERITY_WARNING Logger::Severity::Warning
#define SEVERITY_ERROR Logger::Severity::Error

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

private:
	Logger() {}

public:
	static void Log(Logger::Severity const severity,
		std::string const message,
		std::source_location const source = std::source_location::current());
};

#endif