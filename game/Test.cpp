#include <PalmEngineConfig.h>
#include <rendering/Shader.h>
#include <rendering/Model.h>
#include <resource_manager/ResourceManager.h>

using namespace PalmEngine;

Shader shader;
Model testModel;

void Start()
{
	std::string rootDir(ResourceManager::GetProjectRootDirectory());
	shader = Shader(rootDir + "/resources/shaders/shader.vert", rootDir + "/resources/shaders/shader.frag");
	testModel = Model(rootDir + "/resources/models/scp173/cb_scp173.fbx");
}

void Update()
{
	shader.Use();

	// View/Projection Transformations
	glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)PE_CONFIG_SCREEN_WIDTH / (float)PE_CONFIG_SCREEN_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	shader.SetMat4("projection", projection);
	shader.SetMat4("view", view);

	// Render the loaded model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
	shader.SetMat4("model", model);
	testModel.Draw(shader);
}