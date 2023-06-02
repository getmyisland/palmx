#include <glad/glad.h>

#include "RenderManager.h"

#include <logging/LogManager.h>

namespace PalmEngine
{
	RenderManager::RenderManager() {};
	RenderManager::~RenderManager() {};

	template<> RenderManager* PalmEngineSingleton<RenderManager>::msSingleton = 0;
	RenderManager* RenderManager::GetSingletonPtr(void)
	{
		return msSingleton;
	}
	RenderManager& RenderManager::GetSingleton(void)
	{
		return (*msSingleton);
	}

	void RenderManager::StartUp()
	{
		// Load all OpenGL function pointers
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			PE_LOG_MANAGER->LogError("Failed to initialize GLAD");
			return;
		}

		PE_LOG_MANAGER->LogInfo("Render Manager initialized");
	}

	void RenderManager::ShutDown()
	{

	}

	void RenderManager::Render(GLFWwindow* window, Scene* scene)
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (scene->GetMainCamera() != nullptr)
		{
			for (auto& entity : scene->GetEntitiesInScene())
			{
				entity->Render(scene->GetMainCamera());
			}
		}

		// Check and calls events
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}