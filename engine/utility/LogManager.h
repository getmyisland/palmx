#ifndef PALMX_LOG_MANAGER_H_
#define PALMX_LOG_MANAGER_H_

#define DEBUG_LOG_INFO palmx::LogManager::GetSingleton().LogInfo
#define DEBUG_LOG_WARNING palmx::LogManager::GetSingleton().LogWarning
#define DEBUG_LOG_ERROR palmx::LogManager::GetSingleton().LogError

#include <Singleton.h>

#include <source_location>
#include <string>

namespace palmx
{
	class LogManager : public Singleton<LogManager>
	{
	public:
		LogManager();
		~LogManager();

		static LogManager& GetSingleton(void);
		static LogManager* GetSingletonPtr(void);

		void StartUp();
		void ShutDown();

		void LogInfo(std::string const message,
			std::source_location const source = std::source_location::current());

		void LogWarning(std::string const message,
			std::source_location const source = std::source_location::current());

		void LogError(std::string const message,
			std::source_location const source = std::source_location::current());
	};
}

#endif