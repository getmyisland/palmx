#include <glad/glad.h>

#include "RenderSystem.h"

#include "Renderer.h"
#include "Model.h"
#include "Shader.h"
#include "../engine/Entity.h"
#include "../engine/Logger.h"
#include "../engine/SceneView.h"
#include "../engine/ResourceManager.h"

namespace palmx
{
	RenderSystem::RenderSystem() {};
	RenderSystem::~RenderSystem() {};

	void RenderSystem::Start()
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

	void RenderSystem::Stop()
	{
		LOG_INFO("Render Module stopped");
	}

	void RenderSystem::Render(GLFWwindow* window, Scene* scene)
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

			glm::mat4 view = scene->GetMainCamera()->GetViewMatrix();
			_shader->SetMat4("view", view);

			for (EntityID entity : SceneView<Transform, Renderer>(*scene))
			{
				Renderer* entityRenderer = scene->GetComponent<Renderer>(entity);
				Transform* entityTransform = scene->GetComponent<Transform>(entity);

				if (entityRenderer->mModel == nullptr)
				{
					// Make sure there is a model specified otherwise go to the next entity
					continue;
				}

				for (auto& mesh : entityRenderer->mModel->GetMeshes())
				{
					// Render the mesh
					glm::mat4 model = glm::mat4(1.0f);
					model = glm::translate(model, entityTransform->GetPosition());
					model = glm::scale(model, entityTransform->GetScale());
					_shader->SetMat4("model", model);

					glActiveTexture(GL_TEXTURE0 + 0);
					// Set the sampler to the correct texture unit
					glUniform1i(glGetUniformLocation(_shader->mId, "texture_albedo"), 0);
					// Bind the texture
					glBindTexture(GL_TEXTURE_2D, mesh.GetAlbedoTexture()->mId);

					glActiveTexture(GL_TEXTURE0 + 1);
					// Set the sampler to the correct texture unit
					glUniform1i(glGetUniformLocation(_shader->mId, "texture_normal"), 1);
					// Bind the texture
					glBindTexture(GL_TEXTURE_2D, mesh.GetNormalTexture()->mId);

					// Draw mesh
					glBindVertexArray(mesh.GetVAO());
					glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(mesh.GetIndices().size()), GL_UNSIGNED_INT, 0);
					glBindVertexArray(0);

					// Set everything back to default
					glActiveTexture(GL_TEXTURE0);
				}
			}
		}

		// Check and calls events
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}