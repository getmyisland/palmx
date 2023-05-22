#ifndef _PE_LOGGER_H__
#define _PE_LOGGER_H__

#define PE_LOGGER_LOG PalmEngine::Logger::Log

#define PE_DEBUG PalmEngine::Logger::Severity::Debug
#define PE_INFO PalmEngine::Logger::Severity::Info
#define PE_WARNING PalmEngine::Logger::Severity::Warning
#define PE_ERROR PalmEngine::Logger::Severity::Error

#include <string>
#include <source_location>

namespace PalmEngine
{
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
}

#endif