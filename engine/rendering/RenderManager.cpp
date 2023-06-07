#include <glad/glad.h>

#include "RenderManager.h"

#include <logging/LogManager.h>
#include <scene/components/Renderer.h>
#include <scene/components/Transform.h>
#include <scene/Entity.h>
#include <scene/SceneView.h>

namespace PalmEngine
{
	RenderManager::RenderManager() {};
	RenderManager::~RenderManager() {};

	template<> RenderManager* PalmEngineSingleton<RenderManager>::ms_Singleton = 0;
	RenderManager* RenderManager::GetSingletonPtr(void)
	{
		return ms_Singleton;
	}
	RenderManager& RenderManager::GetSingleton(void)
	{
		return (*ms_Singleton);
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
			for (EntityID ent : SceneView<Transform, Renderer>(*scene))
			{
				scene->GetComponent<Renderer>(ent)->Render(*scene->GetMainCamera(), *scene->GetComponent<Transform>(ent));
			}
		}

		// Check and calls events
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}