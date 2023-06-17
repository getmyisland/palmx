#ifndef PALMX_RENDER_MANAGER_H_
#define PALMX_RENDER_MANAGER_H_

#include <Singleton.h>
#include <entity/Scene.h>

#include <GLFW/glfw3.h>

#include <memory>

namespace palmx
{
	class Shader;

	class RenderManager : public Singleton<RenderManager>
	{
	public:
		RenderManager();
		~RenderManager();

		void StartUp();
		void ShutDown();

		static RenderManager& GetSingleton(void);
		static RenderManager* GetSingletonPtr(void);

		void Render(GLFWwindow* window, Scene* scene);

	private:
		std::shared_ptr<Shader> _shader;
	};
}

#endif