#include "InputModule.h"

#include "../engine/Logger.h"
#include "Input.h"

namespace palmx
{
	InputModule::InputModule() {};
	InputModule::~InputModule() {};

	void InputModule::Start(GLFWwindow* mainWindow)
	{
		glfwSetCursorPosCallback(mainWindow, Input::MouseCallback);
		glfwSetScrollCallback(mainWindow, Input::ScrollCallback);

		LOG_INFO("Input Module started");
	}

	void InputModule::Stop()
	{
		LOG_INFO("Input Module stopped");
	}

	void InputModule::CollectInput(GLFWwindow* window)
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