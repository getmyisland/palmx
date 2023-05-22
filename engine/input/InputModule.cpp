#include "InputModule.h"

#include <logger/Logger.h>

PalmEngine::InputModule::InputModule() {};
PalmEngine::InputModule::~InputModule() {};

void PalmEngine::InputModule::StartUp()
{
	PE_LOGGER_LOG(PE_INFO, "Input Module initialized");
}

void PalmEngine::InputModule::CollectInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void PalmEngine::InputModule::ShutDown()
{

}