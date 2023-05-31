#include "InputManager.h"

#include <logging/LogManager.h>
#include "Input.h"

namespace PalmEngine
{
	InputManager::InputManager() {};
	InputManager::~InputManager() {};

	template<> InputManager* PalmEngineSingleton<InputManager>::msSingleton = 0;
	InputManager* InputManager::GetSingletonPtr(void)
	{
		return msSingleton;
	}
	InputManager& InputManager::GetSingleton(void)
	{
		return (*msSingleton);
	}

	void InputManager::StartUp()
	{
		PE_LOG_MANAGER->LogInfo("Input Module initialized");
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
	}
}