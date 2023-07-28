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

		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		// Create a render texture and framebuffer the scene can render to before being displayed
		glGenFramebuffers(1, &_renderTextureFramebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, _renderTextureFramebuffer);

		glGenTextures(1, &_renderTexture);
		glBindTexture(GL_TEXTURE_2D, _renderTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _renderTextureWidth, _renderTextureHeigth, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		GLuint renderTextureRenderbuffer;
		glGenRenderbuffers(1, &renderTextureRenderbuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, renderTextureRenderbuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _renderTextureWidth, _renderTextureHeigth);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderTextureRenderbuffer);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, _renderTexture, 0);

		GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, drawBuffers);

		GLfloat quadVertices[] = {
	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // Bottom-left vertex
	1.0f, -1.0f, 0.0f, 1.0f, 0.0f,  // Bottom-right vertex
	1.0f, 1.0f, 0.0f, 1.0f, 1.0f,   // Top-right vertex
	-1.0f, 1.0f, 0.0f, 0.0f, 1.0f    // Top-left vertex
		};

		glGenVertexArrays(1, &_fullscreenQuadVertexArray);
		glGenBuffers(1, &_fullscreenQuadVertexBuffer);

		glBindVertexArray(_fullscreenQuadVertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, _fullscreenQuadVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		_defaultShader = ResourceLoader::LoadShader(
			"default_shader", 
			std::string(palmx::ResourceLoader::GetProjectRootDirectory() + "/data/shaders/default_shader.vert").c_str(),
			std::string(palmx::ResourceLoader::GetProjectRootDirectory() + "/data/shaders/default_shader.frag").c_str()
		);
		
		
		_fullscreenQuadShader = ResourceLoader::LoadShader(
			"fullscreen_quad_shader", 
			std::string(palmx::ResourceLoader::GetProjectRootDirectory() + "/data/shaders/fullscreen_quad_shader.vert").c_str(), 
			std::string(palmx::ResourceLoader::GetProjectRootDirectory() + "/data/shaders/fullscreen_quad_shader.frag").c_str()
		);

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
		glBindFramebuffer(GL_FRAMEBUFFER, _renderTextureFramebuffer);
		glViewport(0, 0, _renderTextureWidth, _renderTextureHeigth);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (_defaultShader != nullptr && scene->GetMainCamera() != nullptr)
		{
			_defaultShader.get()->Use();

			int windowWidth, windowHeight;
			glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
			glm::mat4 projection = glm::perspective(glm::radians(scene->GetMainCamera()->mCamera->mZoom), static_cast<float>(windowWidth) / static_cast<float>(windowHeight), 0.1f, 100.0f);
			_defaultShader->SetMat4("projection", projection);

			glm::mat4 view = scene->GetMainCamera()->GetViewMatrix();
			_defaultShader->SetMat4("view", view);

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
					_defaultShader->SetMat4("mesh", meshMat4);

					glActiveTexture(GL_TEXTURE0 + 0);
					// Set the sampler to the correct texture unit
					glUniform1i(glGetUniformLocation(_defaultShader->mId, "texture_albedo"), 0);
					// Bind the texture
					glBindTexture(GL_TEXTURE_2D, mesh.GetAlbedoTexture()->mId);

					glActiveTexture(GL_TEXTURE0 + 1);
					// Set the sampler to the correct texture unit
					glUniform1i(glGetUniformLocation(_defaultShader->mId, "texture_normal"), 1);
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

		_fullscreenQuadShader->Use();

		glBindTexture(GL_TEXTURE_2D, _renderTexture);
		glBindVertexArray(_fullscreenQuadVertexArray);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		// Check and calls events
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}