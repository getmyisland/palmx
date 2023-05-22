#include <glad/glad.h>

#include "RenderModule.h"

#include <PalmEngineConfig.h>
#include <logger/Logger.h>
#include <resource_manager/ResourceManager.h>

PalmEngine::RenderModule::RenderModule() {};
PalmEngine::RenderModule::~RenderModule() {};

void PalmEngine::RenderModule::StartUp()
{
	// Load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		PE_LOGGER_LOG(PE_ERROR, "Failed to initialize GLAD");
		PE_MODULE_MANAGER.KillGameLoop();
		return;
	}

	PE_LOGGER_LOG(PE_INFO, "Render Module initialized");
}

void PalmEngine::RenderModule::Render(GLFWwindow* window)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Check and calls events
	// Swap buffers
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void PalmEngine::RenderModule::ShutDown()
{
	
}