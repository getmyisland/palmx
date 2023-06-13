#include <glad/glad.h>

#include "RenderManager.h"

#include <logging/LogManager.h>
#include <scene/components/Renderer.h>
#include <scene/components/Transform.h>
#include <scene/Entity.h>
#include <scene/SceneView.h>

namespace palmx
{
	RenderManager::RenderManager() {};
	RenderManager::~RenderManager() {};

	template<> RenderManager* Singleton<RenderManager>::msSingleton = 0;
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
			DEBUG_LOG_ERROR("Failed to initialize GLAD");
			return;
		}

		DEBUG_LOG_INFO("Render Manager initialized");
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