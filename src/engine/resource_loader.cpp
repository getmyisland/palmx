#include <glad/glad.h>

#include "resource_loader.h"

#include "logger.h"
#include "../renderer/model.h"
#include "../renderer/shader.h"

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
	std::unordered_map<std::string, std::shared_ptr<render::Shader>> palmx::ResourceLoader::_cachedShaders;
	std::unordered_map<std::string, std::shared_ptr<render::Texture>> palmx::ResourceLoader::_cachedTextures;

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

	std::shared_ptr<render::Shader> ResourceLoader::LoadShader(std::string name, const char* vertexShaderSource, const char* fragmentShaderSource)
	{
		// Check if shader has been loader already, if so; return earlier loaded shader
		auto it = _cachedShaders.find(name);
		if (it != _cachedShaders.end())
		{
			return it->second;
		}

		std::shared_ptr<render::Shader> shader(new render::Shader);
		// Retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// Ensures ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::badbit);
		try
		{
			// Open files
			vShaderFile.open(vertexShaderSource);
			fShaderFile.open(fragmentShaderSource);
			std::stringstream vShaderStream, fShaderStream;
			// Read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// Convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			LOG_ERROR("Shader file not successfully read");
		}
		const GLchar* vShaderCode = vertexCode.c_str();
		const GLchar* fShaderCode = fragmentCode.c_str();

		// Now create and store shader object from source code
		shader->Compile(vShaderCode, fShaderCode, std::string(vertexShaderSource).substr(0, std::string(vertexShaderSource).find_last_of('/')));
		shader->mName = name;
		_cachedShaders[name] = shader;
		return shader;
	}

	std::shared_ptr<render::Shader> ResourceLoader::GetShader(std::string name)
	{
		auto it = _cachedShaders.find(name);
		if (it != _cachedShaders.end())
		{
			return it->second;
		}
		else
		{
			return std::shared_ptr<render::Shader>();
		}
	}

	std::shared_ptr<render::Texture> ResourceLoader::LoadTexture(std::string name, const char* textureSource)
	{
		// Check if texture has been loader already, if so; return earlier loaded texture
		auto it = _cachedTextures.find(name);
		if (it != _cachedTextures.end())
		{
			return it->second;
		}

		std::shared_ptr<render::Texture> texture(new render::Texture);
		unsigned int textureID;
		glGenTextures(1, &textureID);

		int width, height, nrComponents;
		unsigned char* data = stbi_load(textureSource, &width, &height, &nrComponents, 0);
		if (data)
		{
			GLenum format = GL_RGB;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			
			texture->mId = textureID;

			stbi_image_free(data);
		}
		else
		{
			LOG_ERROR("Texture failed to load at path: " + std::string(textureSource));
			stbi_image_free(data);
		}

		// Store and return
		_cachedTextures[name] = texture;
		return texture;
	}

	std::shared_ptr<render::Texture> ResourceLoader::GetTexture(std::string name)
	{
		auto it = _cachedTextures.find(name);
		if (it != _cachedTextures.end())
		{
			return it->second;
		}
		else
		{
			return std::shared_ptr<render::Texture>();
		}
	}

}