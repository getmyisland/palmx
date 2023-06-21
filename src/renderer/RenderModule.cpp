#include <glad/glad.h>

#include "RenderModule.h"

#include "Renderer.h"
#include "Shader.h"
#include "../engine/Transform.h"
#include "../engine/Entity.h"
#include "../engine/Logger.h"
#include "../engine/SceneView.h"
#include "../engine/ResourceManager.h"

namespace palmx
{
	RenderModule::RenderModule() {};
	RenderModule::~RenderModule() {};

	void RenderModule::Start()
	{
		// Load all OpenGL function pointers
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOG_ERROR("Failed to initialize GLAD");
			return;
		}

		_shader = ResourceManager::LoadShader("default", DEFAULT_SHADER_VERTEX, DEFAULT_SHADER_FRAGMENT);

		LOG_INFO("Render Module started");
	}

	void RenderModule::Stop()
	{
		LOG_INFO("Render Module stopped");
	}

	void RenderModule::Render(GLFWwindow* window, Scene* scene)
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