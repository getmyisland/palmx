#include <glad/glad.h>

#include <rendering/Shader.h>
#include <rendering/Model.h>
#include <scene/Scene.h>
#include <scene/SceneManager.h>
#include <PalmEngineRoot.h>

int main()
{
	// First initialize the engine before creating any objects
	PalmEngine::PalmEngineConfig config(800, 600);
	PalmEngine::PalmEngineRoot palmEngineRoot(config);

	PalmEngine::Scene scene;

	//PalmEngine::Entity testEntity(std::string("Test"), nullptr);

	std::string rootDir(PalmEngine::ResourceManager::GetProjectRootDirectory());
	PalmEngine::Shader shader(rootDir + "/resources/shaders/shader.vert", rootDir + "/resources/shaders/shader.frag");
	PalmEngine::Model testModel(rootDir + "/resources/models/scp173/cb_scp173.fbx", shader);
	//testEntity.mModel.reset(&testModel);

	PalmEngine::SceneManager::GetSingletonPtr()->SetActiveScene(scene);

	// After all required objects have been created run the engine
	palmEngineRoot.Run();

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