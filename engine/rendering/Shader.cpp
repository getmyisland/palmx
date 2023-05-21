#include "Shader.h"

#include <glad/glad.h>

#include <palm_engine/logger/Logger.h>
#include <palm_engine/resource_manager/ResourceManager.h>

PalmEngine::Shader::Shader() {}

PalmEngine::Shader::Shader(std::string vertexShaderFilePath, std::string fragmentShaderFilePath)
{
	// Vertex Shader File Content
	std::string vertexFileContent = ResourceManager::GetFileContentAsString(vertexShaderFilePath);
	const char* vertexShaderCode = vertexFileContent.c_str();

	// Fragment Shader File Content
	std::string fragmentFileContent = ResourceManager::GetFileContentAsString(fragmentShaderFilePath);
	const char* fragmentShaderCode = fragmentFileContent.c_str();

	// Compile shaders
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexShaderCode, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		PE_LOGGER_LOG(PE_ERROR, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" + std::string(infoLog));
	};

	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		PE_LOGGER_LOG(PE_ERROR, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" + std::string(infoLog));
	};

	// Shader Program
	mID = glCreateProgram();
	glAttachShader(mID, vertex);
	glAttachShader(mID, fragment);
	glLinkProgram(mID);

	glGetProgramiv(mID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(mID, 512, NULL, infoLog);
		PE_LOGGER_LOG(PE_ERROR, "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" + std::string(infoLog));
	}

	// Delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void PalmEngine::Shader::Use()
{
	glUseProgram(mID);
}

void PalmEngine::Shader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(mID, name.c_str()), (int)value);
}
void PalmEngine::Shader::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(mID, name.c_str()), value);
}
void PalmEngine::Shader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(mID, name.c_str()), value);
}
void PalmEngine::Shader::SetMat4(const std::string& name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(mID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}