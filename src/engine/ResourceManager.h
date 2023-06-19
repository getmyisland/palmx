#ifndef PALMX_RESOURCE_MANAGER_H_
#define PALMX_RESOURCE_MANAGER_H_

#include <memory>
#include <string>
#include <unordered_map>

namespace palmx
{
	class Shader;
	struct Texture;

	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();

		static std::string GetProjectRootDirectory();

		static std::shared_ptr<Shader> LoadShader(std::string name, const char* vertexShaderSource, const char* fragmentShaderSource);
		static std::shared_ptr<Shader> GetShader(std::string name);
		static std::shared_ptr<Texture> LoadTexture(std::string name, const char* textureSource);
		static std::shared_ptr<Texture> GetTexture(std::string name);

	private:
		static std::unordered_map<std::string, std::shared_ptr<Shader>> _cachedShaders;
		static std::unordered_map<std::string, std::shared_ptr<Texture>> _cachedTextures;
	};
}

#endif