#include "fps_controller.h"
#include "target_dummy.h"

#include <palmx/engine.h>
#include <palmx/entity.h>
#include <palmx/scene.h>
#include <palmx/script_hook.h>
#include <palmx/transform.h>
#include <palmx/resource_loader.h>
#include <palmx/camera.h>
#include <palmx/model.h>
#include <palmx/renderer.h>
#include <palmx/shader.h>
#include <palmx/rigidbody.h>

using namespace palmx;

int main()
{
	// Initialize the engine before creating any objects
	Config config("palmx fps example", 1280, 720);
	Engine engine(config);

	// Create the scene object which acts as an entity container
	Scene scene;

	// Create a test entity
	EntityID target_dummy_entity = scene.NewEntity();
	scene.AddComponent<Transform>(target_dummy_entity);
	std::string root_dir(ResourceLoader::GetProjectRootDirectory());
	render::Model target_dummy_model(root_dir + "/data/models/scp173/cb_scp173.fbx");
	render::Renderer* target_dummy_renderer = scene.AddComponent<render::Renderer>(target_dummy_entity);
	target_dummy_renderer->model = std::make_unique<render::Model>(target_dummy_model);
	physics::Rigidbody* target_dummy_rigid_body = scene.AddComponent<physics::Rigidbody>(target_dummy_entity);
	target_dummy_rigid_body->is_dynamic = false;
	ScriptHook* target_dummy_hook = scene.AddComponent<ScriptHook>(target_dummy_entity);
	TargetDummy target_dummy;
	target_dummy_hook->AddScriptBehavior(target_dummy);

	// Create the player entity
	EntityID player = scene.NewEntity();
	Transform* transform = scene.AddComponent<Transform>(player);

	// Running custom scripts requires a hook
	ScriptHook* hook = scene.AddComponent<ScriptHook>(player);
	// Add a custom script to the hook
	FpsController controller;
	hook->AddScriptBehavior(controller);

	// Rendering requires a main camera
	render::Camera* camera = scene.AddComponent<render::Camera>(player);
	MainCamera main_camera(camera, transform);
	scene.SetMainCamera(main_camera);

	// After all required objects have been created run the engine
	engine.Run(scene);

	return 0;
}