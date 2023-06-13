#include <glad/glad.h>

#include <glm/vec3.hpp>
#include <glm/gtx/string_cast.hpp>

#include <Root.h>

#include <scene/Entity.h>
#include <rendering/Shader.h>
#include <rendering/Model.h>
#include <scene/components/Renderer.h>
#include <scene/components/ScriptHook.h>
#include <scene/Scene.h>

#include "PlayerController.h"

using namespace palmx;

int main()
{
	// First initialize the engine before creating any objects
	Config config(800, 600);
	Root palmEngineRoot(config);

	// Create the scene object which acts as an entity container
	Scene scene;

	// Create a test entity
	EntityID testEntity = scene.NewEntity();
	scene.AddComponent<Transform>(testEntity);
	std::string rootDir(ResourceManager::GetProjectRootDirectory());
	Shader shader(rootDir + "/resources/shaders/shader.vert", rootDir + "/resources/shaders/shader.frag");
	Model testModel(rootDir + "/resources/models/scp173/cb_scp173.fbx");
	Renderer* testRenderer = scene.AddComponent<Renderer>(testEntity);
	testRenderer->SetModel(testModel);
	testRenderer->SetShader(shader);

	// Create the player
	EntityID player = scene.NewEntity();
	Transform* transform = scene.AddComponent<Transform>(player);

	// Running custom scripts requires a hook
	scene.AddComponent<ScriptHook>(player);

	// Add a custom script to the hook
	PlayerController controller;
	scene.GetComponent<ScriptHook>(player)->AddScriptBehavior(controller);

	// Rendering requires a main camera
	Camera* camera = scene.AddComponent<Camera>(player);
	MainCamera mainCamera(*camera, *transform);
	scene.SetMainCamera(&mainCamera);

	// After all required objects have been created run the engine
	palmEngineRoot.Run(scene);

	return 0;
}