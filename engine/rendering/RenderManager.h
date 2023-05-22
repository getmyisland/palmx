#ifndef _PE_RENDER_MANAGER_H__
#define _PE_RENDER_MANAGER_H__

#include <PalmEngineSingleton.h>
#include <PalmEngineManager.h>
#include "Shader.h"
#include "Model.h"

#include <GLFW/glfw3.h>

namespace PalmEngine
{
	class RenderManager : PalmEngineManager, public PalmEngineSingleton<RenderManager>
	{
	public:
		RenderManager();
		~RenderManager();

		virtual void StartUp() override;
		virtual void ShutDown() override;

		static RenderManager& GetSingleton(void);
		static RenderManager* GetSingletonPtr(void);

		void Render(GLFWwindow* window);
	};
}

#endif