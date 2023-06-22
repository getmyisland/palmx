#ifndef PALMX_RENDER_SYSTEM_H_
#define PALMX_RENDER_SYSTEM_H_

#include "../engine/Scene.h"

#include <GLFW/glfw3.h>

#include <memory>

namespace palmx
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