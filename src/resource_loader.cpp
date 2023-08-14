#include <glad/glad.h>

#include <palmx/resource_loader.h>

#include <palmx/logger.h>
#include <palmx/model.h>
#include <palmx/shader.h>

#ifndef STBI_INCLUDE_STB_IMAGE_H
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#endif

#include <fstream>
#include <sstream>
#include <iostream>

#include <direct.h>
#define GET_CURRENT_DIR _getcwd

namespace palmx
{
	std::unordered_map<std::string, std::shared_ptr<render::Shader>> palmx::ResourceLoader::cached_shaders_;
	std::unordered_map<std::string, std::shared_ptr<render::Texture>> palmx::ResourceLoader::cached_textures_;

	ResourceLoader::ResourceLoader() {}
	ResourceLoader::~ResourceLoader() {}

	std::string ResourceLoader::GetProjectRootDirectory()
	{
		char buff[FILENAME_MAX]; // Create string buffer to hold path
		char* content = GET_CURRENT_DIR(buff, FILENAME_MAX);
		if (content != NULL)
		{
			return std::string(content);
		}
		else
		{
			LOG_WARNING("Could not get project root directory");
			return std::string("");
		}
	}

	std::shared_ptr<render::Shader> ResourceLoader::LoadShader(std::string name, const char* vertex_shader_source, const char* fragment_shader_source)
	{
		// Check if shader has been loader already, if so; return earlier loaded shader
		auto it = cached_shaders_.find(name);
		if (it != cached_shaders_.end())
		{
			return it->second;
		}

		// Retrieve the vertex/fragment source code from filePath
		std::string vertex_shader_code;
		std::string fragment_shader_code;
		std::ifstream vertex_shader_file;
		std::ifstream fragment_shader_file;
		// Ensures ifstream objects can throw exceptions:
		vertex_shader_file.exceptions(std::ifstream::badbit);
		fragment_shader_file.exceptions(std::ifstream::badbit);
		try
		{
			// Open files
			vertex_shader_file.open(vertex_shader_source);
			fragment_shader_file.open(fragment_shader_source);
			std::stringstream vertex_shader_stream, fragment_shader_stream;
			// Read file's buffer contents into streams
			vertex_shader_stream << vertex_shader_file.rdbuf();
			fragment_shader_stream << fragment_shader_file.rdbuf();
			// close file handlers
			vertex_shader_file.close();
			fragment_shader_file.close();
			// Convert stream into string
			vertex_shader_code = vertex_shader_stream.str();
			fragment_shader_code = fragment_shader_stream.str();
		}
		catch (std::ifstream::failure e)
		{
			LOG_ERROR("Shader file not successfully read");
		}
		const GLchar* vertex_shader_code_c = vertex_shader_code.c_str();
		const GLchar* fragment_shader_code_c = fragment_shader_code.c_str();

		// Now create and store shader object from source code
		std::shared_ptr<render::Shader> shader(new render::Shader(name));
		shader->Compile(vertex_shader_code_c, fragment_shader_code_c, std::string(vertex_shader_source).substr(0, std::string(vertex_shader_source).find_last_of('/')));
		cached_shaders_[name] = shader;
		return shader;
	}

	std::shared_ptr<render::Shader> ResourceLoader::GetShader(std::string name)
	{
		auto it = cached_shaders_.find(name);
		if (it != cached_shaders_.end())
		{
			return it->second;
		}
		else
		{
			return std::shared_ptr<render::Shader>();
		}
	}

	std::shared_ptr<render::Texture> ResourceLoader::LoadTexture(std::string name, const char* texture_source)
	{
		// Check if texture has been loader already, if so; return earlier loaded texture
		auto it = cached_textures_.find(name);
		if (it != cached_textures_.end())
		{
			return it->second;
		}

		std::shared_ptr<render::Texture> texture(new render::Texture);
		unsigned int texture_id;
		glGenTextures(1, &texture_id);

		int width, height, num_components;
		unsigned char* data = stbi_load(texture_source, &width, &height, &num_components, 0);
		if (data)
		{
			GLenum format = GL_RGB;
			if (num_components == 1)
				format = GL_RED;
			else if (num_components == 3)
				format = GL_RGB;
			else if (num_components == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, texture_id);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			texture->id = texture_id;

			stbi_image_free(data);
		}
		else
		{
			LOG_ERROR("Texture failed to load at path: " + std::string(texture_source));
			stbi_image_free(data);
		}

		// Store and return
		cached_textures_[name] = texture;
		return texture;
	}

	std::shared_ptr<render::Texture> ResourceLoader::GetTexture(std::string name)
	{
		auto it = cached_textures_.find(name);
		if (it != cached_textures_.end())
		{
			return it->second;
		}
		else
		{
			return std::shared_ptr<render::Texture>();
		}
	}

}