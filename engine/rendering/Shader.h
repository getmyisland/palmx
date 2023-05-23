#ifndef _PE_SHADER_H__
#define _PE_SHADER_H__

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace PalmEngine
{
	class Shader
	{
	public:
		Shader(std::string vertexShaderFilePath, std::string fragmentShaderFilePath);

	private:
		Shader();

	public:
		unsigned int mID = 0;

		void Use();

		void SetBool(const std::string& name, bool value) const;
		void SetInt(const std::string& name, int value) const;
		void SetFloat(const std::string& name, float value) const;
		void SetMat4(const std::string& name, glm::mat4 value) const;
	};
}

#endif