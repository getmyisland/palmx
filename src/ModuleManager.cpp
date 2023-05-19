#include "ModuleManager.h"
#include "Modules.h"

GLFWwindow* ModuleManager::GetApplicationWindow()
{
	return m_pWindow;
}

void ModuleManager::StartEngine(GLFWwindow* pWindow)
{
	m_pWindow = pWindow;

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
	while (!glfwWindowShouldClose(m_pWindow))
	{
		UpdateModules();
		RenderModules();
	}
}

void ModuleManager::UpdateModules()
{
	Modules::g_InputModule.CollectInput(m_pWindow);
}

void ModuleManager::RenderModules()
{
	Modules::g_RenderModule.Render(m_pWindow);
}

void ModuleManager::ShutdownModules()
{
	Modules::g_InputModule.Shutdown();
	Modules::g_RenderModule.Shutdown();
}

void ModuleManager::KillGameLoop()
{
	glfwSetWindowShouldClose(m_pWindow, true);
}