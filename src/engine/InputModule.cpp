#include "InputModule.h"

#include "../engine/Logger.h"
#include "Input.h"

namespace palmx
{
	InputModule::InputModule() {};
	InputModule::~InputModule() {};

	void InputModule::StartUp(GLFWwindow* mainWindow)
	{
		glfwSetCursorPosCallback(mainWindow, Input::MouseCallback);
		glfwSetScrollCallback(mainWindow, Input::ScrollCallback);

		LOG_INFO("Input Manager initialized");
	}

	void InputModule::ShutDown()
	{

	}

	void InputModule::CollectInput(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}

		Input::SetKeyStates(window);
		Input::ResetMouseOffset();
	}
}