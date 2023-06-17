#include <glad/glad.h>

#include "RenderManager.h"

#include <filesystem/ResourceManager.h>
#include <logging/LogManager.h>
#include <entity/Renderer.h>
#include <entity/Transform.h>
#include <entity/Entity.h>
#include <entity/SceneView.h>
#include <rendering/Shader.h>

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

		_shader = ResourceManager::GetSingletonPtr()->LoadShader("default", DEFAULT_SHADER_VERTEX, DEFAULT_SHADER_FRAGMENT);

		DEBUG_LOG_INFO("Render Manager initialized");
	}

	void RenderManager::ShutDown()
	{

	}

	void RenderManager::Render(GLFWwindow* window, Scene* scene)
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (_shader != nullptr && scene->GetMainCamera() != nullptr)
		{
			_shader.get()->Use();

			int windowWidth, windowHeight;
			glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
			glm::mat4 projection = glm::perspective(glm::radians(scene->GetMainCamera()->mCamera->mZoom), static_cast<float>(windowWidth) / static_cast<float>(windowHeight), 0.1f, 100.0f);
			_shader->SetMat4("projection", projection);

			glm::mat4 view = scene->GetMainCamera()->mCamera->GetViewMatrix(*scene->GetMainCamera()->mTransform);
			_shader->SetMat4("view", view);

			for (EntityID ent : SceneView<Transform, Renderer>(*scene))
			{
				scene->GetComponent<Renderer>(ent)->Render(_shader, *scene->GetComponent<Transform>(ent));
			}
		}

		// Check and calls events
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}