#ifndef _PE_RENDER_MANAGER_H__
#define _PE_RENDER_MANAGER_H__

#include <PalmEngineManager.h>
#include "Shader.h"
#include "Model.h"

#include <GLFW/glfw3.h>

namespace PalmEngine
{
	class RenderManager : public PalmEngineManager
	{
	public:
		RenderManager();
		~RenderManager();

		virtual void StartUp() override;
		virtual void ShutDown() override;

		void Render(GLFWwindow* window);
	};
}

#endif