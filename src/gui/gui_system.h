#ifndef PALMX_GUI_SYSTEM_H
#define PALMX_GUI_SYSTEM_H

#include <GLFW/glfw3.h>

namespace palmx::gui
{
	class GuiSystem
	{
	public:
		GuiSystem();
		~GuiSystem();

		void Start(unsigned int width, unsigned int height);
		void Stop();

		GLFWwindow* GetMainWindow() const;
		void ResizeMainWindow(unsigned int width, unsigned int height);

	private:
		GLFWwindow* _mainWindow = nullptr;
	};
}

#endif