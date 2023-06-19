#include "GuiModule.h"

#include "../engine/Logger.h"

namespace palmx
{
	void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

	GuiModule::GuiModule() { }	
	GuiModule::~GuiModule() { }

	void GuiModule::StartUp(unsigned int width, unsigned int height)
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
		_mainWindow = glfwCreateWindow(width, height, "Palm Engine", NULL, NULL);
		if (_mainWindow == nullptr)
		{
			LOG_ERROR("Failed to create GLFW window");
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(_mainWindow);
		glfwSetFramebufferSizeCallback(_mainWindow, FramebufferSizeCallback);

		glfwSetInputMode(_mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		LOG_INFO("Window Manager initialized");
	}

	void GuiModule::ShutDown()
	{
		glfwTerminate();
	}

	GLFWwindow* GuiModule::GetMainWindow() const
	{
		return _mainWindow;
	}

	void GuiModule::ResizeMainWindow(unsigned int width, unsigned int height)
	{
		FramebufferSizeCallback(_mainWindow, width, height);
	}

	void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		// Make sure the viewport matches the new window dimensions; note that width and 
		// Height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);
	}
}