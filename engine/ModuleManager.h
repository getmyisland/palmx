#ifndef _PE_MODULE_MANAGER_H__
#define _PE_MODULE_MANAGER_H__

#define PE_MODULE_MANAGER PalmEngine::ModuleManager::GetInstance()

#include <GLFW/glfw3.h>

namespace PalmEngine
{
	class ModuleManager
	{
	public:
		static ModuleManager& GetInstance()
		{
			static ModuleManager sInstance;

			return sInstance;
		}

		ModuleManager(ModuleManager const&) = delete;
		void operator=(ModuleManager const&) = delete;

	private:
		ModuleManager() {};

		GLFWwindow* _window = nullptr;

		void StartUpModules();
		void GameLoop();
		void UpdateModules();
		void RenderModules();
		void ShutdownModules();

	public:
		void Run(GLFWwindow* window);
		void KillGameLoop();
	};
}

#endif