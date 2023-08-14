#include <glad/glad.h>

#include <palmx/shader.h>

#include <palmx/logger.h>

#include <fstream>
#include <iostream>
#include <sstream>

namespace palmx::render
{
    Shader::Shader() {}
    Shader::~Shader() {}

    void Shader::Compile(const char* vertex_source, const char* fragment_source, std::string directory)
    {
        // First pre-process shaders with preprocessor (includes, pragma defines etc.)
        std::string vertex_shader_code_processed = PreProcess(std::string(vertex_source), directory);
        std::string fragment_shader_code_processed = PreProcess(std::string(fragment_source), directory);
        const GLchar* vertex_shader_code = vertex_shader_code_processed.c_str();
        const GLchar* fragment_shader_code = fragment_shader_code_processed.c_str();

        // Then process pre-processed shader source
        GLuint vertex_shader;
        GLuint fragment_shader;
        // Vertex Shader
        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &vertex_shader_code, NULL);
        glCompileShader(vertex_shader);
        CheckCompileErrors(vertex_shader, VERTEX);
        // Fragment Shader
        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &fragment_shader_code, NULL);
        glCompileShader(fragment_shader);
        CheckCompileErrors(fragment_shader, FRAGMENT);
        // Shader Program
        id_ = glCreateProgram();
        glAttachShader(id_, vertex_shader);
        glAttachShader(id_, fragment_shader);
        glLinkProgram(id_);
        CheckCompileErrors(id_, PROGRAM);
        // Delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
    }

    std::string Shader::PreProcess(std::string shader_code, std::string directory)
    {
        if (directory == "")
        {
            // May only be the case when loading predefined shaders
            return shader_code;
        }

        std::stringstream input(shader_code);
        std::stringstream output;
        std::string line;
        while (std::getline(input, line))
        {
            if (line.substr(0, 15) == "#pragma include")
            {
                std::string filepath = line.substr(16);
                if (filepath != "")
                {
                    filepath = directory + "/" + filepath;
                }
                std::ifstream file(filepath);
                while (std::getline(file, line))
                {
                    output << line << std::endl;
                }
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
        glUseProgram(id_);
    }

    void Shader::SetBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(id_, name.c_str()), (int)value);
    }
    void Shader::SetInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(id_, name.c_str()), value);
    }
    void Shader::SetFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(id_, name.c_str()), value);
    }
    void Shader::SetMat4(const std::string& name, glm::mat4 value) const
    {
        glUniformMatrix4fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }

    void Shader::CheckCompileErrors(GLuint object, ShaderType type)
    {
        GLint success;
        char info_log[1024];
        if (type != ShaderType::PROGRAM)
        {
            glGetShaderiv(object, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(object, 1024, NULL, info_log);
                Logger::Error("Shader compilation failed for type " + std::to_string(type) + "\n" + std::string(info_log));
            }
        }
        else
        {
            glGetProgramiv(object, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(object, 1024, NULL, info_log);
                Logger::Error("Shader program linking failed\n" + std::string(info_log));
            }
        }
    }
}