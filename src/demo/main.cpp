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
	EntityID test_entity = scene.NewEntity();
	scene.AddComponent<Transform>(test_entity);
	std::string root_dir(ResourceLoader::GetProjectRootDirectory());
	render::Model test_model(root_dir + "/data/models/scp173/cb_scp173.fbx");
	render::Renderer* test_renderer = scene.AddComponent<render::Renderer>(test_entity);
	test_renderer->model = std::make_unique<render::Model>(test_model);
	physics::Rigidbody* rigid_body = scene.AddComponent<physics::Rigidbody>(test_entity);
	rigid_body->is_dynamic = true;
	ScriptHook* test_hook = scene.AddComponent<ScriptHook>(test_entity);
	DemoEnemy demo_enemy;
	test_hook->AddScriptBehavior(demo_enemy);

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
	MainCamera main_camera(camera, transform);
	scene.SetMainCamera(main_camera);

	// After all required objects have been created run the engine
	engine.Run(scene);

	return 0;
}