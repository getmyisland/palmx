#include <glad/glad.h>

#include "RenderManager.h"

#include <logging/LogManager.h>

// DEBUG ONLY NOT NEEDED HERE
#include <filesystem/ResourceManager.h>

namespace PalmEngine
{
	Shader shader;
	Model testModel;

	RenderManager::RenderManager() {};
	RenderManager::~RenderManager() {};

	//-----------------------------------------------------------------------

	template<> RenderManager* PalmEngineSingleton<RenderManager>::msSingleton = 0;
	RenderManager* RenderManager::GetSingletonPtr(void)
	{
		return msSingleton;
	}
	RenderManager& RenderManager::GetSingleton(void)
	{
		return (*msSingleton);
	}

	//-----------------------------------------------------------------------

	void RenderManager::StartUp()
	{
		// Load all OpenGL function pointers
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			PE_LOG_MANAGER->LogError("Failed to initialize GLAD");
			//PE_MODULE_MANAGER.KillGameLoop();
			return;
		}

		std::string rootDir(ResourceManager::GetProjectRootDirectory());
		shader = Shader(rootDir + "/resources/shaders/shader.vert", rootDir + "/resources/shaders/shader.frag");
		testModel = Model(rootDir + "/resources/models/scp173/cb_scp173.fbx");

		PE_LOG_MANAGER->LogInfo("Render Module initialized");
	}

	void RenderManager::ShutDown()
	{

	}

	//-----------------------------------------------------------------------

	void RenderManager::Render(GLFWwindow* window)
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// DEBUG ONLY //////////////////////////////////////////////
		shader.Use();

		// View/Projection Transformations
		glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)800 / (float)600, 0.1f, 100.0f);
		glm::mat4 view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		shader.SetMat4("projection", projection);
		shader.SetMat4("view", view);

		// Render the loaded model
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		shader.SetMat4("model", model);
		testModel.Draw(shader);
		// DEBUG ONLY END //////////////////////////////////////////////

		// Check and calls events
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}