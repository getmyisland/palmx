#include <glad/glad.h>

#include "RenderModule.h"

#include <palm_engine/logger/Logger.h>
#include <palm_engine/resource_manager/ResourceManager.h>

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

	std::string rootDir(ResourceManager::GetProjectRootDirectory());
	_shader = Shader(rootDir + "/resources/shaders/shader.vs", rootDir + "/resources/shaders/shader.fs");
	
	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
	};

	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);
	
	glGenBuffers(1, &_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	PE_LOGGER_LOG(PE_INFO, "Render Module initialized");
}

void PalmEngine::RenderModule::Render(GLFWwindow* pWindow)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	_shader.Use();

	glBindVertexArray(_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// Check and calls events
	// Swap buffers
	glfwSwapBuffers(pWindow);
	glfwPollEvents();
}

void PalmEngine::RenderModule::ShutDown()
{
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_VBO);
}