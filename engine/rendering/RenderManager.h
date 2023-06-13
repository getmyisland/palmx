#ifndef PALMX_RENDER_MANAGER_H_
#define PALMX_RENDER_MANAGER_H_

#include <GLFW/glfw3.h>

#include <Singleton.h>

#include <entity/Scene.h>

namespace palmx
{
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
	};
}

#endif