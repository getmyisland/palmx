#include <glad/glad.h>

#include "render_system.h"

#include "renderer.h"
#include "model.h"
#include "shader.h"
#include "../engine/entity.h"
#include "../engine/logger.h"
#include "../engine/scene_view.h"
#include "../engine/resource_loader.h"

namespace palmx::render
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

		_shader = ResourceLoader::LoadShader("default_shader", DEFAULT_VERTEX_SHADER_PATH, DEFAULT_FRAGMENT_SHADER_PATH);
		_screenShader = ResourceLoader::LoadShader("default_screen_shader", VERTEX_SCREEN_SHADER_PATH, FRAGMENT_SCREEN_SHADER_PATH);

		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		// Create a virtual render texture and framebuffer the scene can render to before being displayed
		glGenFramebuffers(1, &_psxFrameBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, _psxFrameBuffer);

		glGenTextures(1, &_renderTexture);
		glBindTexture(GL_TEXTURE_2D, _renderTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _virtualScreenWidth, _virtualScreenHeigth, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		_screenShader->Use();
		_screenShader->SetInt("renderTexture", _renderTexture);

		GLuint depthRenderBuffer;
		glGenRenderbuffers(1, &depthRenderBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthRenderBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _virtualScreenWidth, _virtualScreenHeigth);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderBuffer);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, _renderTexture, 0);

		GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, drawBuffers);

		// Create a quad on which the render texture will be displayed upon
		glGenVertexArrays(1, &_quadVertexArray);
		glBindVertexArray(_quadVertexArray);

		const GLfloat quadVertexBufferData[] = {
			-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			-1.0f, 1.0f, 0.0f,
			-1.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
		};

		GLuint quadVertexBuffer;
		glGenBuffers(1, &quadVertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, quadVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertexBufferData), quadVertexBufferData, GL_STATIC_DRAW);

		LOG_INFO("Render System started");
	}

	void RenderSystem::Stop()
	{
		LOG_INFO("Render System stopped");
	}

	void RenderSystem::Render(GLFWwindow* window, Scene* scene)
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Always render the scene at a lower resolution to emulate the ps1 screen
		// Everything below will now be rendered to the render texture instead of the screen directly
		glBindFramebuffer(GL_FRAMEBUFFER, _psxFrameBuffer);
		glViewport(0, 0, _virtualScreenWidth, _virtualScreenHeigth);

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
					glm::mat4 meshMat4 = glm::mat4(1.0f);
					meshMat4 = glm::translate(meshMat4, entityTransform->GetPosition());
					meshMat4 = glm::scale(meshMat4, entityTransform->GetScale());
					_shader->SetMat4("mesh", meshMat4);

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

		int width, height;
		glfwGetWindowSize(window, &width, &height);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, width, height);

		_screenShader->Use();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _renderTexture);
		// Problem might be because I'm binding the textures wrong?

		glBindVertexArray(_quadVertexArray);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		// Check and calls events
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}