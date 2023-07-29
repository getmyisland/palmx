#include "gui_system.h"

#include "../engine/logger.h"

namespace palmx::gui
{
	void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

	GuiSystem::GuiSystem() { }	
	GuiSystem::~GuiSystem() { }

	void GuiSystem::Start(unsigned int width, unsigned int height)
	{
		// Initialize and configure glfw
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		// Create glfw window
		main_window_ = glfwCreateWindow(width, height, "palmx", NULL, NULL);
		if (main_window_ == nullptr)
		{
			LOG_ERROR("Failed to create GLFW window.");
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(main_window_);
		glfwSetFramebufferSizeCallback(main_window_, FramebufferSizeCallback);

		glfwSetInputMode(main_window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		LOG_INFO("Gui System started");
	}

	void GuiSystem::Stop()
	{
		glfwTerminate();

		LOG_INFO("Gui System stopped");
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