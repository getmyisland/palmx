#include "InputModule.h"

#include <palm_engine/logger/Logger.h>

PalmEngine::InputModule::InputModule() {};
PalmEngine::InputModule::~InputModule() {};

void PalmEngine::InputModule::StartUp()
{
	PE_LOGGER_LOG(PE_INFO, "Input Module initialized");
}

void PalmEngine::InputModule::CollectInput(GLFWwindow* pWindow)
{
	if (glfwGetKey(pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(pWindow, true);
	}
}

void PalmEngine::InputModule::ShutDown()
{

}