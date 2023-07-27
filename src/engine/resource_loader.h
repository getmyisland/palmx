#ifndef PALMX_RESOURCE_LOADER_H
#define PALMX_RESOURCE_LOADER_H

#include <memory>
#include <string>
#include <unordered_map>

namespace palmx
{
	namespace render
	{
		class Shader;
		struct Texture;
	}

	class ResourceLoader
	{
	public:
		ResourceLoader();
		~ResourceLoader();

		static std::string GetProjectRootDirectory();

		static std::shared_ptr<render::Shader> LoadShader(std::string name, const char* vertexShaderSource, const char* fragmentShaderSource);
		static std::shared_ptr<render::Shader> GetShader(std::string name);
		static std::shared_ptr<render::Texture> LoadTexture(std::string name, const char* textureSource);
		static std::shared_ptr<render::Texture> GetTexture(std::string name);

	private:
		static std::unordered_map<std::string, std::shared_ptr<render::Shader>> _cachedShaders;
		static std::unordered_map<std::string, std::shared_ptr<render::Texture>> _cachedTextures;
	};
}

#endif