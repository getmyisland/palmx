#ifndef _PE_RENDER_MODULE_H__
#define _PE_RENDER_MODULE_H__

#include "../IModule.h"
#include "Shader.h"

#include <GLFW/glfw3.h>

namespace PalmEngine
{
	class RenderModule : public IModule
	{
	public:
		RenderModule();
		~RenderModule();

		virtual void StartUp() override;
		virtual void ShutDown() override;

		void Render(GLFWwindow* pWindow);

	private:
		Shader _shader;

		unsigned int _VAO = 0;
		unsigned int _VBO = 0;
	};
}

#endif