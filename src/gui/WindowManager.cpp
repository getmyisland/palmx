#include "WindowManager.h"

#include <logging/LogManager.h>
#include <Root.h>

namespace palmx
{
	void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

	WindowManager::WindowManager() { }	
	WindowManager::~WindowManager() { }

	template<> WindowManager* Singleton<WindowManager>::msSingleton = 0;
	WindowManager* WindowManager::GetSingletonPtr(void)
	{
		return msSingleton;
	}
	WindowManager& WindowManager::GetSingleton(void)
	{
		return (*msSingleton);
	}

	void WindowManager::StartUp(unsigned int width, unsigned int height)
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
			DEBUG_LOG_ERROR("Failed to create GLFW window");
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(_mainWindow);
		glfwSetFramebufferSizeCallback(_mainWindow, FramebufferSizeCallback);

		glfwSetInputMode(_mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		DEBUG_LOG_INFO("Window Manager initialized");
	}

	void WindowManager::ShutDown()
	{
		glfwTerminate();
	}

	GLFWwindow* WindowManager::GetMainWindow() const
	{
		return _mainWindow;
	}

	void WindowManager::ResizeMainWindow(unsigned int width, unsigned int height)
	{
		FramebufferSizeCallback(_mainWindow, width, height);
	}

	void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		palmx::Root::GetSingletonPtr()->mpConfig->mWidth = width;
		palmx::Root::GetSingletonPtr()->mpConfig->mHeight = height;

		// Make sure the viewport matches the new window dimensions; note that width and 
		// Height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);
	}
}