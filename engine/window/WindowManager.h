#ifndef _PE_WINDOW_MANAGER_H__
#define _PE_WINDOW_MANAGER_H__

#include <PalmEngineSingleton.h>

#include <GLFW/glfw3.h>

namespace PalmEngine
{
	class WindowManager : public PalmEngineSingleton<WindowManager>
	{
	public:
		WindowManager();
		~WindowManager();

		static WindowManager& GetSingleton(void);
		static WindowManager* GetSingletonPtr(void);

		void StartUp();
		void ShutDown();

	public:
		GLFWwindow* GetMainWindow() const;

	private:
		GLFWwindow* _mainWindow = nullptr;
	};
}

#endif