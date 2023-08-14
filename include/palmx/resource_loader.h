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

		static std::shared_ptr<render::Shader> LoadShader(std::string name, const char* vertex_shader_source, const char* fragment_shader_source);
		static std::shared_ptr<render::Shader> GetShader(std::string name);
		static std::shared_ptr<render::Texture> LoadTexture(std::string name, const char* texture_source);
		static std::shared_ptr<render::Texture> GetTexture(std::string name);

	private:
		static std::unordered_map<std::string, std::shared_ptr<render::Shader>> cached_shaders_;
		static std::unordered_map<std::string, std::shared_ptr<render::Texture>> cached_textures_;
	};
}

#endif