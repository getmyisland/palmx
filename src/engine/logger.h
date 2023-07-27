#ifndef PALMX_LOGGER_H
#define PALMX_LOGGER_H

#define LOG_INFO palmx::Logger::LogInfo
#define LOG_WARNING palmx::Logger::LogWarning
#define LOG_ERROR palmx::Logger::LogError

#include <source_location>
#include <string>

namespace palmx
{
	class Logger
	{
	public:
		static void LogInfo(std::string const message,
			std::source_location const source = std::source_location::current());

		static void LogWarning(std::string const message,
			std::source_location const source = std::source_location::current());

		static void LogError(std::string const message,
			std::source_location const source = std::source_location::current());

	private:
		Logger();
		~Logger();
	};
}

#endif