#include "InputModule.h"

#include <palm_engine/logger/Logger.h>

InputModule::InputModule() {};
InputModule::~InputModule() {};

void InputModule::Init()
{
	Logger::Log(SEVERITY_INFO, "Input Module initialized");
}

void InputModule::CollectInput(GLFWwindow* pWindow)
{
	if (glfwGetKey(pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(pWindow, true);
	}
}

void InputModule::Shutdown()
{

}