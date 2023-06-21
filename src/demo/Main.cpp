#include "DemoController.h"

#include "../engine/Engine.h"
#include "../engine/Entity.h"
#include "../engine/Scene.h"
#include "../engine/ScriptHook.h"
#include "../engine/Transform.h"
#include "../renderer/Camera.h"
#include "../renderer/Model.h"
#include "../renderer/Renderer.h"
#include "../renderer/Shader.h"

#include <glm/vec3.hpp>
#include <glm/gtx/string_cast.hpp>

using namespace palmx;

int main()
{
	// Initialize the engine before creating any objects
	Config config(800, 600);
	Engine engine(config);

	// Create the scene object which acts as an entity container
	Scene scene;

	// Create a test entity
	EntityID testEntity = scene.NewEntity();
	scene.AddComponent<Transform>(testEntity);
	std::string rootDir(ResourceManager::GetProjectRootDirectory());
	Model testModel(rootDir + "/data/models/scp173/cb_scp173.fbx");
	Renderer* testRenderer = scene.AddComponent<Renderer>(testEntity);
	testRenderer->mModel = std::make_unique<Model>(testModel);

	// Create the player entity
	EntityID player = scene.NewEntity();
	Transform* transform = scene.AddComponent<Transform>(player);

	// Running custom scripts requires a hook
	ScriptHook* hook = scene.AddComponent<ScriptHook>(player);
	// Add a custom script to the hook
	DemoController controller;
	hook->AddScriptBehavior(controller);

	// Rendering requires a main camera
	Camera* camera = scene.AddComponent<Camera>(player);
	MainCamera mainCamera(camera, transform);
	scene.SetMainCamera(mainCamera);

	// After all required objects have been created run the engine
	engine.Run(scene);

	return 0;
}