#include "InputManager.h"

#include <logging/LogManager.h>

PalmEngine::InputManager::InputManager() {};
PalmEngine::InputManager::~InputManager() {};

void PalmEngine::InputManager::StartUp()
{
	PE_LOG_MANAGER->LogInfo("Input Module initialized");
}

void PalmEngine::InputManager::CollectInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void PalmEngine::InputManager::ShutDown()
{

}