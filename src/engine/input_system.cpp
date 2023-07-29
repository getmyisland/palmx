#include "input_system.h"

#include "input.h"
#include "../engine/logger.h"

namespace palmx
{
	InputSystem::InputSystem() {};
	InputSystem::~InputSystem() {};

	void InputSystem::Start(GLFWwindow* main_window)
	{
		glfwSetCursorPosCallback(main_window, Input::MouseCallback);
		glfwSetScrollCallback(main_window, Input::ScrollCallback);

		LOG_INFO("Input System started");
	}

	void InputSystem::Stop()
	{
		LOG_INFO("Input System stopped");
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