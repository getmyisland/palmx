#include "Shader.h"

#include <glad/glad.h>

#include <palm_engine/logger/Logger.h>
#include <palm_engine/file_system/FileSystem.h>

Shader::Shader(std::string vertexShaderFilePath, std::string fragmentShaderFilePath)
{
	// Vertex Shader File Content
	std::string vertexFileContent = FileSystem::GetFileContent(vertexShaderFilePath);
	const char* vertexShaderCode = vertexFileContent.c_str();

	// Fragment Shader File Content
	std::string fragmentFileContent = FileSystem::GetFileContent(fragmentShaderFilePath);
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
		Logger::Log(SEVERITY_ERROR, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" + std::string(infoLog));
	};

	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		Logger::Log(SEVERITY_ERROR, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" + std::string(infoLog));
	};

	// Shader Program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		Logger::Log(SEVERITY_ERROR, "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" + std::string(infoLog));
	}

	// Delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::Use()
{
	glUseProgram(ID);
}

void Shader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::SetMat4(const std::string& name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}