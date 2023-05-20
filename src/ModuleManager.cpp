#include "ModuleManager.h"
#include "Modules.h"

GLFWwindow* ModuleManager::GetApplicationWindow()
{
	return _pWindow;
}

void ModuleManager::StartEngine(GLFWwindow* pWindow)
{
	_pWindow = pWindow;

	InitModules();
	GameLoop();
	ShutdownModules();
}

void ModuleManager::InitModules()
{
	Modules::g_InputModule.Init();
	Modules::g_RenderModule.Init();
}

void ModuleManager::GameLoop()
{
	while (!glfwWindowShouldClose(_pWindow))
	{
		UpdateModules();
		RenderModules();
	}
}

void ModuleManager::UpdateModules()
{
	Modules::g_InputModule.CollectInput(_pWindow);
}

void ModuleManager::RenderModules()
{
	Modules::g_RenderModule.Render(_pWindow);
}

void ModuleManager::ShutdownModules()
{
	Modules::g_InputModule.Shutdown();
	Modules::g_RenderModule.Shutdown();
}

void ModuleManager::KillGameLoop()
{
	glfwSetWindowShouldClose(_pWindow, true);
}