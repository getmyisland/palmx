#ifndef PALMX_GUI_MODULE_H_
#define PALMX_GUI_MODULE_H_

#include <GLFW/glfw3.h>

namespace palmx
{
	class GuiModule
	{
	public:
		GuiModule();
		~GuiModule();

		void Start(unsigned int width, unsigned int height);
		void Stop();

		GLFWwindow* GetMainWindow() const;
		void ResizeMainWindow(unsigned int width, unsigned int height);

	private:
		GLFWwindow* _mainWindow = nullptr;
	};
}

#endif