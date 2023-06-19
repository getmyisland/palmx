#ifndef PALMX_RESOURCE_MANAGER_H_
#define PALMX_RESOURCE_MANAGER_H_

#include <Singleton.h>

#include <memory>
#include <string>
#include <unordered_map>

namespace palmx
{
	class Shader;
	struct Texture;

	class ResourceManager : public Singleton<ResourceManager>
	{
	public:
		ResourceManager();
		~ResourceManager();

		void StartUp();
		void ShutDown();

		static ResourceManager& GetSingleton(void);
		static ResourceManager* GetSingletonPtr(void);

		std::string GetProjectRootDirectory();

		std::shared_ptr<Shader> LoadShader(std::string name, const char* vertexShaderSource, const char* fragmentShaderSource);
		std::shared_ptr<Shader> GetShader(std::string name);
		std::shared_ptr<Texture> LoadTexture(std::string name, const char* textureSource);
		std::shared_ptr<Texture> GetTexture(std::string name);

	private:
		std::unordered_map<std::string, std::shared_ptr<Shader>> _cachedShaders;
		std::unordered_map<std::string, std::shared_ptr<Texture>> _cachedTextures;
	};
}

#endif