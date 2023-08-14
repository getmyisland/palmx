#include <palmx/input_system.h>

#include <palmx/input.h>
#include <palmx/logger.h>

namespace palmx
{
	InputSystem::InputSystem() {};
	InputSystem::~InputSystem() {};

	void InputSystem::Start(GLFWwindow* main_window)
	{
		glfwSetCursorPosCallback(main_window, Input::MouseCallback);
		glfwSetScrollCallback(main_window, Input::ScrollCallback);

		Logger::Info("Input System started");
	}

	void InputSystem::Stop()
	{
		Logger::Info("Input System stopped");
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