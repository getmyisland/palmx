#include <glad/glad.h>

#include "RenderModule.h"

#include <palm_engine/logger/Logger.h>
#include <palm_engine/file_system/FileSystem.h>

RenderModule::RenderModule() {};
RenderModule::~RenderModule() {};

void RenderModule::Init()
{
	// Load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Logger::Log(SEVERITY_ERROR, "Failed to initialize GLAD");
		MODULE_MANAGER.KillGameLoop();
		return;
	}

	std::string rootDir(FileSystem::GetProjectRootDirectory());
	shader = Shader(rootDir + "/src/rendering/shaders/shader.vs", rootDir + "/src/rendering/shaders/shader.fs");
	
	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	Logger::Log(SEVERITY_INFO, "Render Module initialized");
}

void RenderModule::Render(GLFWwindow* pWindow)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	shader.Use();

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// Check and calls events
	// Swap buffers
	glfwSwapBuffers(pWindow);
	glfwPollEvents();
}

void RenderModule::Shutdown()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}