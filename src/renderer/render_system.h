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
		GLuint _renderTextureFramebuffer{ 0 };
		GLuint _renderTexture{ 0 };
		const unsigned int _renderTextureWidth{ 320 };
		const unsigned int _renderTextureHeigth{ 224 };

		GLuint _fullscreenQuadVertexBuffer{ 0 };
		GLuint _fullscreenQuadVertexArray{ 0 };
		std::shared_ptr<Shader> _fullscreenQuadShader{ nullptr };

		std::shared_ptr<Shader> _defaultShader{ nullptr };
	};
}

#endif