#include "Scene.h"

#include <algorithm>

namespace PalmEngine
{
	Scene::Scene() {}

	Scene::Scene(std::string name) : _name(name) { }

	Scene::~Scene() {}

	std::string Scene::GetName() const
	{
		return _name;
	}

	Camera* Scene::GetMainCamera()
	{
		return _mainCamera;
	}

	void Scene::SetMainCamera(Camera& mainCamera)
	{
		_mainCamera = &mainCamera;
	}

	std::vector<Entity*> Scene::GetEntitiesInScene() const
	{
		return _entitiesInScene;
	}

	void Scene::AddEntityToScene(Entity& entity)
	{
		_entitiesInScene.push_back(&entity);
	}

	void Scene::RemoveEntityFromScene(Entity& entity)
	{
		_entitiesInScene.erase(std::remove(_entitiesInScene.begin(), _entitiesInScene.end(), &entity), _entitiesInScene.end());
	}

	void Scene::OnLoad()
	{

	}

	void Scene::OnUnload()
	{

	}
}