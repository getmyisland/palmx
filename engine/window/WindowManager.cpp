#include "WindowManager.h"

#include <PalmEngineRoot.h>
#include <logging/LogManager.h>

namespace PalmEngine
{
	void FramebufferSizeCallback(GLFWwindow* pWindow, int width, int height);

	WindowManager::WindowManager() { }
	
	WindowManager::~WindowManager() { }

	template<> WindowManager* PalmEngineSingleton<WindowManager>::ms_Singleton = 0;
	WindowManager* WindowManager::GetSingletonPtr(void)
	{
		return ms_Singleton;
	}
	WindowManager& WindowManager::GetSingleton(void)
	{
		return (*ms_Singleton);
	}

	void WindowManager::StartUp()
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
		_mainWindow = glfwCreateWindow(PalmEngineRoot::GetSingletonPtr()->m_pConfig->GetWidth(), PalmEngineRoot::GetSingletonPtr()->m_pConfig->GetHeight(), "Palm Engine", NULL, NULL);
		if (_mainWindow == nullptr)
		{
			PE_LOG_MANAGER->LogError("Failed to create GLFW window");
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(_mainWindow);
		glfwSetFramebufferSizeCallback(_mainWindow, FramebufferSizeCallback);

		glfwSetInputMode(_mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		PE_LOG_MANAGER->LogInfo("Window Manager initialized");
	}

	void WindowManager::ShutDown()
	{
		glfwTerminate();
	}

	GLFWwindow* WindowManager::GetMainWindow() const
	{
		return _mainWindow;
	}

	void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		PalmEngineRoot::GetSingletonPtr()->m_pConfig->SetWidth(width);
		PalmEngineRoot::GetSingletonPtr()->m_pConfig->SetHeight(height);

		// Make sure the viewport matches the new window dimensions; note that width and 
		// Height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);
	}
}