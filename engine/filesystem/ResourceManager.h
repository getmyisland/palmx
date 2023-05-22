#ifndef _PE_RESOURCE_MANAGER_H__
#define _PE_RESOURCE_MANAGER_H__

#include <PalmEngineManager.h>
#include <string>

namespace PalmEngine
{
	class ResourceManager : PalmEngineManager
	{
	public:
		ResourceManager();
		~ResourceManager();

		virtual void StartUp() override;
		virtual void ShutDown() override;

		static std::string GetProjectRootDirectory();
		static std::string GetFileContentAsString(std::string& filePath);
	};
}

#endif