#ifndef PALMX_WINDOW_MANAGER_H_
#define PALMX_WINDOW_MANAGER_H_

#include <GLFW/glfw3.h>

#include <Singleton.h>

namespace palmx
{
	class WindowManager : public Singleton<WindowManager>
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