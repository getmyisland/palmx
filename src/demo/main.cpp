#include "demo_controller.h"
#include "demo_enemy.h"

#include "../engine/engine.h"
#include "../engine/entity.h"
#include "../engine/scene.h"
#include "../engine/script_hook.h"
#include "../engine/transform.h"
#include "../engine/resource_loader.h"
#include "../renderer/camera.h"
#include "../renderer/model.h"
#include "../renderer/renderer.h"
#include "../renderer/shader.h"
#include "../physics/rigidbody.h"

#include <glm/vec3.hpp>
#include <glm/gtx/string_cast.hpp>

using namespace palmx;

int main()
{
	// Initialize the engine before creating any objects
	Config config(1280, 720);
	Engine engine(config);

	// Create the scene object which acts as an entity container
	Scene scene;

	// Create a test entity
	EntityID testEntity = scene.NewEntity();
	scene.AddComponent<Transform>(testEntity);
	std::string rootDir(ResourceLoader::GetProjectRootDirectory());
	render::Model testModel(rootDir + "/data/models/scp173/cb_scp173.fbx");
	render::Renderer* testRenderer = scene.AddComponent<render::Renderer>(testEntity);
	testRenderer->mModel = std::make_unique<render::Model>(testModel);
	physics::Rigidbody* rigidBody = scene.AddComponent<physics::Rigidbody>(testEntity);
	rigidBody->mIsDynamic = true;
	ScriptHook* testHook = scene.AddComponent<ScriptHook>(testEntity);
	DemoEnemy scp173;
	testHook->AddScriptBehavior(scp173);

	// Create the player entity
	EntityID player = scene.NewEntity();
	Transform* transform = scene.AddComponent<Transform>(player);

	// Running custom scripts requires a hook
	ScriptHook* hook = scene.AddComponent<ScriptHook>(player);
	// Add a custom script to the hook
	DemoController controller;
	hook->AddScriptBehavior(controller);

	// Rendering requires a main camera
	render::Camera* camera = scene.AddComponent<render::Camera>(player);
	MainCamera mainCamera(camera, transform);
	scene.SetMainCamera(mainCamera);

	// After all required objects have been created run the engine
	engine.Run(scene);

	return 0;
}