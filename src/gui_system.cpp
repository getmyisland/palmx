#include "gui_system.h"

#include <palmx/logger.h>

namespace palmx::gui
{
	void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

	GuiSystem::GuiSystem() {}
	GuiSystem::~GuiSystem() {}

	void GuiSystem::Start(const char* name, unsigned int width, unsigned int height)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		main_window_ = glfwCreateWindow(width, height, name, NULL, NULL);
		if (main_window_ == nullptr)
		{
			Logger::Error("Failed to create GLFW window.");
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(main_window_);
		glfwSetFramebufferSizeCallback(main_window_, FramebufferSizeCallback);

		glfwSetInputMode(main_window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		Logger::Info("Gui System started");
	}

	void GuiSystem::Stop()
	{
		glfwTerminate();

		Logger::Info("Gui System stopped");
	}

	GLFWwindow* GuiSystem::GetMainWindow() const
	{
		return main_window_;
	}

	void GuiSystem::ResizeMainWindow(unsigned int width, unsigned int height)
	{
		FramebufferSizeCallback(main_window_, width, height);
	}

	void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		// Make sure the viewport matches the new window dimensions; note that width and 
		// Height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);
	}
}