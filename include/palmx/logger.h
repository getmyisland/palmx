#ifndef PALMX_LOGGER_H
#define PALMX_LOGGER_H

#include <source_location>
#include <string>

namespace palmx
{
	class Logger
	{
	public:
		static void Info(std::string const message,
			std::source_location const source = std::source_location::current());

		static void Warning(std::string const message,
			std::source_location const source = std::source_location::current());

		static void Error(std::string const message,
			std::source_location const source = std::source_location::current());

	private:
		Logger();
		~Logger();
	};
}

#endif