#include <glad/glad.h>

#include "RenderModule.h"
#include "../PalmEngineConfig.h"

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
	_testModel = Model(rootDir + "/resources/objects/scp173/cb_scp173.fbx");

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

void PalmEngine::RenderModule::Render(GLFWwindow* window)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	_shader.Use();

	// View/Projection Transformations
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)PE_CONFIG_SCREEN_WIDTH / (float)PE_CONFIG_SCREEN_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	_shader.SetMat4("projection", projection);
	_shader.SetMat4("view", view);

	// Render the loaded model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
	_shader.SetMat4("model", model);
	_testModel.Draw(_shader);

	// Check and calls events
	// Swap buffers
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void PalmEngine::RenderModule::ShutDown()
{
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_VBO);
}