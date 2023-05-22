#include <glad/glad.h>

#include "RenderManager.h"

#include <logging/LogManager.h>

namespace PalmEngine
{
	RenderManager::RenderManager() {};
	RenderManager::~RenderManager() {};

	//-----------------------------------------------------------------------

	template<> RenderManager* PalmEngineSingleton<RenderManager>::msSingleton = 0;
	RenderManager* RenderManager::GetSingletonPtr(void)
	{
		return msSingleton;
	}
	RenderManager& RenderManager::GetSingleton(void)
	{
		return (*msSingleton);
	}

	//-----------------------------------------------------------------------

	void RenderManager::StartUp()
	{
		// Load all OpenGL function pointers
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			PE_LOG_MANAGER->LogError("Failed to initialize GLAD");
			//PE_MODULE_MANAGER.KillGameLoop();
			return;
		}

		PE_LOG_MANAGER->LogInfo("Render Module initialized");
	}

	void RenderManager::ShutDown()
	{

	}

	//-----------------------------------------------------------------------

	void RenderManager::Render(GLFWwindow* window)
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Check and calls events
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}