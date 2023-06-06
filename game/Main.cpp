#include <glad/glad.h>

#include <glm/vec3.hpp>
#include <glm/gtx/string_cast.hpp>

#include <scene/Entity.h>
#include <rendering/Shader.h>
#include <rendering/Model.h>
#include <components/Renderer.h>
#include <components/ScriptHook.h>
#include <scene/Scene.h>
#include <PalmEngineRoot.h>
#include "PlayerController.h"

using namespace PalmEngine;

int main()
{
	// First initialize the engine before creating any objects
	PalmEngineConfig config(800, 600);
	PalmEngineRoot palmEngineRoot(config);

	Scene scene;
	EntityID entity = scene.NewEntity();
	scene.AddComponent<Transform>(entity);
	std::string rootDir(ResourceManager::GetProjectRootDirectory());
	Shader shader(rootDir + "/resources/shaders/shader.vert", rootDir + "/resources/shaders/shader.frag");
	Model testModel(rootDir + "/resources/models/scp173/cb_scp173.fbx");
	Renderer* modelRenderer = scene.AddComponent<Renderer>(entity);
	modelRenderer->SetModel(testModel);
	modelRenderer->SetShader(shader);

	EntityID player = scene.NewEntity();
	Transform* transform = scene.AddComponent<Transform>(player);
	scene.AddComponent<ScriptHook>(player);
	PlayerController controller;
	scene.GetComponent<ScriptHook>(player)->AddScriptBehavior(controller);
	Camera* camera = scene.AddComponent<Camera>(player);
	camera->SetTransform(*transform);
	scene.SetMainCamera(camera);

	// After all required objects have been created run the engine
	palmEngineRoot.Run(scene);

	return 0;
}