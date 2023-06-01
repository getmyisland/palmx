#include <glad/glad.h>

#include <entity/Entity.h>
#include <rendering/Shader.h>
#include <rendering/Model.h>
#include <rendering/Renderer.h>
#include <scene/Scene.h>
#include <PalmEngineRoot.h>
#include "PlayerController.h"

using namespace PalmEngine;

int main()
{
	// First initialize the engine before creating any objects
	PalmEngineConfig config(800, 600);
	PalmEngineRoot palmEngineRoot(config);

	Scene scene("Testing");

	Entity entity(std::string("Test Entity"));
	std::string rootDir(ResourceManager::GetProjectRootDirectory());
	Shader shader(rootDir + "/resources/shaders/shader.vert", rootDir + "/resources/shaders/shader.frag");
	Model testModel(rootDir + "/resources/models/scp173/cb_scp173.fbx");
	Renderer modelRenderer(testModel, shader);
	entity.SetRenderer(modelRenderer);
	scene.AddEntityToScene(entity);

	Entity player(std::string("Player"));
	PlayerController playerController;
	Camera camera(*player.GetTransform());
	player.AddScriptBehavior(playerController);
	player.SetCamera(camera);
	scene.AddEntityToScene(player);
	scene.SetMainCamera(camera);

	// After all required objects have been created run the engine
	palmEngineRoot.Run(scene);

	return 0;
}