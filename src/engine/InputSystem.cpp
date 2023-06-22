#include "InputSystem.h"

#include "../engine/Logger.h"
#include "Input.h"

namespace palmx
{
	InputSystem::InputSystem() {};
	InputSystem::~InputSystem() {};

	void InputSystem::Start(GLFWwindow* mainWindow)
	{
		glfwSetCursorPosCallback(mainWindow, Input::MouseCallback);
		glfwSetScrollCallback(mainWindow, Input::ScrollCallback);

		LOG_INFO("Input Module started");
	}

	void InputSystem::Stop()
	{
		LOG_INFO("Input Module stopped");
	}

	void InputSystem::CollectInput(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}

		Input::SetKeyStates(window);
		Input::ResetMouseOffset();
		Input::ResetMouseWheelOffset();
	}
}