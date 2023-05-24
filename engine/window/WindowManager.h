#ifndef _PE_WINDOW_MANAGER__
#define _PE_WINDOW_MANAGER__

#include <PalmEngineManager.h>
#include <PalmEngineSingleton.h>

#include <GLFW/glfw3.h>

namespace PalmEngine
{
	class WindowManager : PalmEngineManager, public PalmEngineSingleton<WindowManager>
	{
	public:
		WindowManager();
		~WindowManager();

		static WindowManager& GetSingleton(void);
		static WindowManager* GetSingletonPtr(void);

		virtual void StartUp() override;
		virtual void ShutDown() override;

	public:
		GLFWwindow* GetMainWindow() const;

	private:
		GLFWwindow* _mainWindow = nullptr;
	};
}

#endif