#ifndef PALMX_RENDER_SYSTEM_H
#define PALMX_RENDER_SYSTEM_H

#include "../engine/scene.h"

#include <GLFW/glfw3.h>

#include <memory>

namespace palmx::render
{
	class Shader;

	class RenderSystem
	{
	public:
		RenderSystem();
		~RenderSystem();

		void Start();
		void Stop();

		void Render(GLFWwindow* window, Scene* scene);

	private:
		GLuint render_texture_{ 0 };
		GLuint render_texture_framebuffer_{ 0 };
		const unsigned int render_texture_width_{ 256 };
		const unsigned int render_texture_heigth_{ 224 };

		GLuint fullscreen_quad_vertex_buffer_{ 0 };
		GLuint fullscreen_quad_vertex_array_{ 0 };
		std::shared_ptr<Shader> fullscreen_quad_shader_{ nullptr };

		std::shared_ptr<Shader> default_shader_{ nullptr };
	};
}

#endif