#include <glad/glad.h>

#include <rendering/Shader.h>
#include <rendering/Model.h>
#include <scene/Scene.h>
#include <PalmEngineRoot.h>

int main()
{
	// This needs to be done at the start or else PalmEngine objects can't be created because some of them rely on OpenGL functions
	// TODO Find a better method
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		PE_LOG_MANAGER->LogError("Failed to initialize GLAD");
		return -1;
	}

	PalmEngine::Scene scene;

	//PalmEngine::Entity testEntity(std::string("Test"), nullptr);

	std::string rootDir(PalmEngine::ResourceManager::GetProjectRootDirectory());
	PalmEngine::Shader shader(rootDir + "/resources/shaders/shader.vert", rootDir + "/resources/shaders/shader.frag");
	PalmEngine::Model testModel(rootDir + "/resources/models/scp173/cb_scp173.fbx", shader);
	//testEntity.mModel.reset(&testModel);

	PalmEngine::PalmEngineConfig config(scene, 800, 600);
	PalmEngine::PalmEngineRoot palmEngineRoot(config);

	return 0;
}

//void Update()
//{
//	shader.Use();
//
//	// View/Projection Transformations
//	glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)800 / (float)600, 0.1f, 100.0f);
//	glm::mat4 view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
//	shader.SetMat4("projection", projection);
//	shader.SetMat4("view", view);
//
//	// Render the loaded model
//	glm::mat4 model = glm::mat4(1.0f);
//	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0f)); // translate it down so it's at the center of the scene
//	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
//	shader.SetMat4("model", model);
//	testModel.Draw();
//}