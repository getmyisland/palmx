#include "InputManager.h"

#include "Input.h"
#include <logging/LogManager.h>

namespace palmx
{
	InputManager::InputManager() {};
	InputManager::~InputManager() {};

	template<> InputManager* Singleton<InputManager>::msSingleton = 0;
	InputManager* InputManager::GetSingletonPtr(void)
	{
		return msSingleton;
	}
	InputManager& InputManager::GetSingleton(void)
	{
		return (*msSingleton);
	}

	void InputManager::StartUp(GLFWwindow* mainWindow)
	{
		glfwSetCursorPosCallback(mainWindow, Input::MouseCallback);
		glfwSetScrollCallback(mainWindow, Input::ScrollCallback);

		DEBUG_LOG_INFO("Input Manager initialized");
	}

	void InputManager::ShutDown()
	{

	}

	void InputManager::CollectInput(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}

		Input::SetKeyStates(window);
		Input::ResetMouseOffset();
	}
}