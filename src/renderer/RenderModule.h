#ifndef PALMX_RENDER_MODULE_H_
#define PALMX_RENDER_MODULE_H_

#include "../engine/Scene.h"

#include <GLFW/glfw3.h>

#include <memory>

namespace palmx
{
	class Shader;

	class RenderModule
	{
	public:
		RenderModule();
		~RenderModule();

		void Start();
		void Stop();

		void Render(GLFWwindow* window, Scene* scene);

	private:
		std::shared_ptr<Shader> _shader{ nullptr };
	};
}

#endif