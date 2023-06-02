#ifndef _PE_RESOURCE_MANAGER_H__
#define _PE_RESOURCE_MANAGER_H__

#define DEFAULT_SHADER_VERTEX PalmEngine::ResourceManager::GetProjectRootDirectory() + "/resources/shaders/shader.vert"
#define DEFAULT_SHADER_FRAGMENT PalmEngine::ResourceManager::GetProjectRootDirectory() + "/resources/shaders/shader.frag"

#include <PalmEngineSingleton.h>
#include <string>

namespace PalmEngine
{
	class ResourceManager : public PalmEngineSingleton<ResourceManager>
	{
	public:
		ResourceManager();
		~ResourceManager();

		void StartUp();
		void ShutDown();

		static ResourceManager& GetSingleton(void);
		static ResourceManager* GetSingletonPtr(void);

		static std::string GetProjectRootDirectory();
		static std::string GetFileContentAsString(std::string& filePath);
	};
}

#endif