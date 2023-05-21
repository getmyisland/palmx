#include "ModuleManager.h"
#include "Modules.h"

void PalmEngine::ModuleManager::Run(GLFWwindow* window)
{
	_window = window;

	StartUpModules();
	GameLoop();
	ShutdownModules();
}

void PalmEngine::ModuleManager::StartUpModules()
{
	gInputModule.StartUp();
	gRenderModule.StartUp();
}

void PalmEngine::ModuleManager::GameLoop()
{
	float deltaTime = 0.0f;	// time between current frame and last frame
	float lastFrame = 0.0f;

	while (!glfwWindowShouldClose(_window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		UpdateModules();
		RenderModules();
	}
}

void PalmEngine::ModuleManager::UpdateModules()
{
	gInputModule.CollectInput(_window);
}

void PalmEngine::ModuleManager::RenderModules()
{
	gRenderModule.Render(_window);
}

void PalmEngine::ModuleManager::ShutdownModules()
{
	gInputModule.ShutDown();
	gRenderModule.ShutDown();
}

void PalmEngine::ModuleManager::KillGameLoop()
{
	glfwSetWindowShouldClose(_window, true);
}