#include <glad/glad.h>

#include <palmx/render_system.h>

#include <palmx/renderer.h>
#include <palmx/model.h>
#include <palmx/shader.h>
#include <palmx/entity.h>
#include <palmx/logger.h>
#include <palmx/scene_view.h>
#include <palmx/resource_loader.h>

namespace palmx::render
{
	const char* default_vertex_shader_source = R"(
		#version 330 core

		layout (location = 0) in vec3 aPos;
		layout (location = 1) in vec3 aNormal;
		layout (location = 2) in vec2 aTexCoord;

		out vec2 texCoord;

		uniform mat4 mesh;
		uniform mat4 view;
		uniform mat4 projection;

		void main()
		{
			gl_Position = projection * view * mesh * vec4(aPos, 1.0);
			texCoord = aTexCoord;
		}
	)";

	const char* default_fragment_shader_source = R"(
		#version 330 core

		in vec3 color;
		in vec2 texCoord;

		out vec4 FragColor;  
				
		uniform sampler2D texture_albedo;
		uniform sampler2D texture_normal;

		void main()
		{
			FragColor = texture(texture_albedo, texCoord);
		}
	)";

	const char* fullscreen_quad_vertex_shader = R"(
		#version 330 core

		layout (location = 0) in vec3 aPos;
		layout (location = 1) in vec2 aTexCoord;

		out vec2 TexCoord;

		void main() {
			gl_Position = vec4(aPos, 1.0);
			TexCoord = aTexCoord;
		}
	)";

	const char* fullscreen_quad_fragment_shader = R"(
		#version 330 core

		in vec2 TexCoord;

		out vec4 FragColor;

		uniform sampler2D renderTexture;

		void main() {
			FragColor = texture(renderTexture, TexCoord);
		}
	)";

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
		glGenFramebuffers(1, &render_texture_framebuffer_);
		glBindFramebuffer(GL_FRAMEBUFFER, render_texture_framebuffer_);

		glGenTextures(1, &render_texture_);
		glBindTexture(GL_TEXTURE_2D, render_texture_);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, render_texture_width_, render_texture_heigth_, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		GLuint render_texture_renderbuffer;
		glGenRenderbuffers(1, &render_texture_renderbuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, render_texture_renderbuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, render_texture_width_, render_texture_heigth_);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, render_texture_renderbuffer);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, render_texture_, 0);

		GLenum draw_buffers[1] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, draw_buffers);

		GLfloat quad_vertices[] = {
	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // Bottom-left vertex
	1.0f, -1.0f, 0.0f, 1.0f, 0.0f,  // Bottom-right vertex
	1.0f, 1.0f, 0.0f, 1.0f, 1.0f,   // Top-right vertex
	-1.0f, 1.0f, 0.0f, 0.0f, 1.0f    // Top-left vertex
		};

		glGenVertexArrays(1, &fullscreen_quad_vertex_array_);
		glGenBuffers(1, &fullscreen_quad_vertex_buffer_);

		glBindVertexArray(fullscreen_quad_vertex_array_);
		glBindBuffer(GL_ARRAY_BUFFER, fullscreen_quad_vertex_buffer_);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), quad_vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		default_shader_ = std::unique_ptr<Shader>(new Shader("default_shader"));
		default_shader_->Compile(default_vertex_shader_source, default_fragment_shader_source, "");

		fullscreen_quad_shader_ = std::unique_ptr<Shader>(new Shader("fullscreen_quad_shader_"));
		fullscreen_quad_shader_->Compile(fullscreen_quad_vertex_shader, fullscreen_quad_fragment_shader, "");

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
		glBindFramebuffer(GL_FRAMEBUFFER, render_texture_framebuffer_);
		glViewport(0, 0, render_texture_width_, render_texture_heigth_);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// TODO Allow user to define their own shader which is optionally applied
		// Depends on how you handle the vertex squiggle

		if (default_shader_ != nullptr && scene->GetMainCamera() != nullptr)
		{
			default_shader_.get()->Use();

			int framebuffer_width, framebuffer_height;
			glfwGetFramebufferSize(window, &framebuffer_width, &framebuffer_height);
			glm::mat4 projection = glm::perspective(glm::radians(scene->GetMainCamera()->GetCamera()->zoom), static_cast<float>(framebuffer_width) / static_cast<float>(framebuffer_height), 0.1f, 100.0f);
			default_shader_->SetMat4("projection", projection);

			glm::mat4 view = scene->GetMainCamera()->GetViewMatrix();
			default_shader_->SetMat4("view", view);

			for (EntityID entity : SceneView<Transform, Renderer>(*scene))
			{
				Renderer* entity_renderer = scene->GetComponent<Renderer>(entity);
				Transform* entity_transform = scene->GetComponent<Transform>(entity);

				if (entity_renderer->model == nullptr)
				{
					// Make sure there is a model specified otherwise go to the next entity
					continue;
				}

				for (auto& mesh : entity_renderer->model->GetMeshes())
				{
					// Render the mesh
					glm::mat4 mesh_mat4 = glm::mat4(1.0f);
					mesh_mat4 = glm::translate(mesh_mat4, entity_transform->GetPosition());
					mesh_mat4 = glm::scale(mesh_mat4, entity_transform->GetScale());
					default_shader_->SetMat4("mesh", mesh_mat4);

					glActiveTexture(GL_TEXTURE0 + 0);
					// Set the sampler to the correct texture unit
					default_shader_->SetInt("texture_albedo", 0);
					// Bind the texture
					glBindTexture(GL_TEXTURE_2D, mesh.GetAlbedoTexture()->id);

					glActiveTexture(GL_TEXTURE0 + 1);
					// Set the sampler to the correct texture unit
					default_shader_->SetInt("texture_normal", 1);
					// Bind the texture
					glBindTexture(GL_TEXTURE_2D, mesh.GetNormalTexture()->id);

					// Draw mesh
					glBindVertexArray(mesh.GetVAO());
					glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(mesh.GetIndices().size()), GL_UNSIGNED_INT, 0);
					glBindVertexArray(0);

					// Set everything back to default
					glActiveTexture(GL_TEXTURE0);
				}
			}
		}

		int window_width, window_height;
		glfwGetWindowSize(window, &window_width, &window_height);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, window_width, window_height);

		fullscreen_quad_shader_->Use();

		glBindTexture(GL_TEXTURE_2D, render_texture_);
		glBindVertexArray(fullscreen_quad_vertex_array_);

		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		// Check and calls events
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}