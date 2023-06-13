#ifndef PALMX_RESOURCE_MANAGER_H_
#define PALMX_RESOURCE_MANAGER_H_

#define DEFAULT_SHADER_VERTEX palmx::ResourceManager::GetProjectRootDirectory() + "/resources/shaders/shader.vert"
#define DEFAULT_SHADER_FRAGMENT palmx::ResourceManager::GetProjectRootDirectory() + "/resources/shaders/shader.frag"

#include <Singleton.h>

#include <string>

namespace palmx
{
	class ResourceManager : public Singleton<ResourceManager>
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