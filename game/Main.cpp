#include <glad/glad.h>

#include <glm/vec3.hpp>
#include <glm/gtx/string_cast.hpp>

#include <scene/Entity.h>
#include <rendering/Shader.h>
#include <rendering/Model.h>
#include <scene/components/Renderer.h>
#include <scene/components/ScriptHook.h>
#include <scene/Scene.h>
#include <PalmEngineRoot.h>

#include "PlayerController.h"

using namespace PalmEngine;

int main()
{
	// First initialize the engine before creating any objects
	PalmEngineConfig config(800, 600);
	PalmEngineRoot palmEngineRoot(config);

	// Create the scene object which acts as an entity container
	Scene scene;

	// Create a test entity
	EntityID testEntity = scene.NewEntity();
	scene.AddComponent<Transform>(testEntity);
	std::string rootDir(ResourceManager::GetProjectRootDirectory());
	Shader shader(rootDir + "/resources/shaders/shader.vert", rootDir + "/resources/shaders/shader.frag");
	Model testModel(rootDir + "/resources/models/scp173/cb_scp173.fbx");
	Renderer* modelRenderer = scene.AddComponent<Renderer>(testEntity);
	modelRenderer->SetModel(testModel);
	modelRenderer->SetShader(shader);

	// Create the player
	EntityID player = scene.NewEntity();
	Transform* transform = scene.AddComponent<Transform>(player);

	// In order to run custom scripts use a ScriptHook and then add a custom ScriptBehavior to it
	scene.AddComponent<ScriptHook>(player);
	PlayerController controller;
	scene.GetComponent<ScriptHook>(player)->AddScriptBehavior(controller);

	// A scene needs a main camera in order to be rendered
	Camera* camera = scene.AddComponent<Camera>(player);
	MainCamera mainCamera(*camera, *transform);
	scene.SetMainCamera(&mainCamera);

	// After all required objects have been created run the engine
	palmEngineRoot.Run(scene);

	return 0;
}