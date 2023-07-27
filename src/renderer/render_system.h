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
		unsigned int _psxFrameBuffer = 0;
		unsigned int _renderTexture = 0;
		unsigned int _quadVertexArray = 0;
		const unsigned int _virtualScreenWidth{ 320 };
		const unsigned int _virtualScreenHeigth{ 224 };

		std::shared_ptr<Shader> _shader{ nullptr };
		std::shared_ptr<Shader> _screenShader{ nullptr };
	};
}

#endif