#ifndef PALMX_SHADER_H
#define PALMX_SHADER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

namespace palmx::render
{
	class Shader
	{
	public:
		Shader(const std::string name) : name_(name) {}
		~Shader();

		void Compile(const char* vertex_source, const char* fragment_source, std::string directory);
		// Pre-processes the source code for custom #pragma directives
		std::string PreProcess(std::string shader_code, std::string directory);

		void Use() const;

		void SetBool(const std::string& name, bool value) const;
		void SetInt(const std::string& name, int value) const;
		void SetFloat(const std::string& name, float value) const;
		void SetMat4(const std::string& name, glm::mat4 value) const;

	private:
		enum ShaderType
		{
			VERTEX,
			FRAGMENT,
			PROGRAM
		};

		Shader();

		const std::string name_{ "shader" };
		unsigned int id_{ 0 };

		void CheckCompileErrors(GLuint object, ShaderType type);
	};
}

#endif