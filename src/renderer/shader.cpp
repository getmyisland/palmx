#include <glad/glad.h>

#include "shader.h"

#include "../engine/logger.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace palmx
{
	Shader::Shader() {}
	Shader::~Shader() {}

    void Shader::Compile(const char* vertexSource, const char* fragmentSource, std::string directory)
    {
        // first pre-process shaders with preprocessor (includes, pragma defines etc.)
        std::string vsCodeProcessed = PreProcess(std::string(vertexSource), directory);
        std::string fsCodeProcessed = PreProcess(std::string(fragmentSource), directory);
        const GLchar* vsCode = vsCodeProcessed.c_str();
        const GLchar* fsCode = fsCodeProcessed.c_str();

        // then process pre-processed shader source
        GLuint sVertex, sFragment;
        // Vertex Shader
        sVertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(sVertex, 1, &vsCode, NULL);
        glCompileShader(sVertex);
        CheckCompileErrors(sVertex, Vertex);
        // Fragment Shader
        sFragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(sFragment, 1, &fsCode, NULL);
        glCompileShader(sFragment);
        CheckCompileErrors(sFragment, Fragment);
        // Shader Program
        mId = glCreateProgram();
        glAttachShader(mId, sVertex);
        glAttachShader(mId, sFragment);
        glLinkProgram(mId);
        CheckCompileErrors(mId, Program);
        // Delete the shaders as they're linked into our program now and no longer necessery
        glDeleteShader(sVertex);
        glDeleteShader(sFragment);
    }

    std::string Shader::PreProcess(std::string shaderCode, std::string directory)
    {
        std::stringstream input(shaderCode);
        std::stringstream output;
        std::string line;
        while (std::getline(input, line))
        {
            if (line.substr(0, 15) == "#pragma include")
            {
                std::string filepath = line.substr(16);
                if (filepath != "")
                    filepath = directory + "/" + filepath;
                std::ifstream file(filepath);
                while (std::getline(file, line))
                    output << line << std::endl;
            }
            else
            {
                output << line << std::endl;
            }
        }
        return output.str();
    }

	void Shader::Use() const
	{
		glUseProgram(mId);
	}

	void Shader::SetBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(mId, name.c_str()), (int)value);
	}
	void Shader::SetInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(mId, name.c_str()), value);
	}
	void Shader::SetFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(mId, name.c_str()), value);
	}
	void Shader::SetMat4(const std::string& name, glm::mat4 value) const
	{
		glUniformMatrix4fv(glGetUniformLocation(mId, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

    void Shader::CheckCompileErrors(GLuint object, ShaderType type)
    {
        GLint success;
        char infoLog[1024];
        if (type != ShaderType::Program)
        {
            glGetShaderiv(object, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(object, 1024, NULL, infoLog);
                LOG_ERROR("Shader compilation failed for type " + std::to_string(type) + "\n" + std::string(infoLog));
            }
        }
        else
        {
            glGetProgramiv(object, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(object, 1024, NULL, infoLog);
                LOG_ERROR("Shader program linking failed\n" + std::string(infoLog));
            }
        }
    }
}