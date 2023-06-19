#ifndef PALMX_SHADER_H_
#define PALMX_SHADER_H_

#define DEFAULT_SHADER_VERTEX std::string(palmx::ResourceManager::GetSingletonPtr()->GetProjectRootDirectory() + "/data/shaders/shader.vert").c_str()
#define DEFAULT_SHADER_FRAGMENT std::string(palmx::ResourceManager::GetSingletonPtr()->GetProjectRootDirectory() + "/data/shaders/shader.frag").c_str()

#include <filesystem/ResourceManager.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

namespace palmx
{
	class Shader
	{
	public:
		Shader();
		~Shader();

		std::string mName;
		unsigned int mID = 0;

		void Compile(const GLchar* vertexSource, const GLchar* fragmentSource, std::string directory);
		// Pre-processes the source code for custom #pragma directives
		std::string PreProcess(std::string shaderCode, std::string directory);

		void Use() const;

		void SetBool(const std::string& name, bool value) const;
		void SetInt(const std::string& name, int value) const;
		void SetFloat(const std::string& name, float value) const;
		void SetMat4(const std::string& name, glm::mat4 value) const;

	private:
		enum ShaderType
		{
			Vertex,
			Fragment,
			Program
		};

		void CheckCompileErrors(GLuint object, ShaderType type);
	};
}

#endif