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
		std::shared_ptr<Shader> _shader{ nullptr };
	};
}

#endif