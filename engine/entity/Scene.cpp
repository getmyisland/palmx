#include "Scene.h"

#include <algorithm>

namespace palmx
{
	Scene::Scene() {}
	Scene::~Scene() {}

	MainCamera* Scene::GetMainCamera()
	{
		return _mainCamera;
	}

	void Scene::SetMainCamera(MainCamera* mainCamera)
	{
		_mainCamera = mainCamera;
	}

	std::vector<Entity> Scene::GetEntitiesInScene() const
	{
		return _entities;
	}

	EntityID Scene::NewEntity()
	{
		if (!_freeEntities.empty())
		{
			EntityIndex newIndex = _freeEntities.back();
			_freeEntities.pop_back();
			EntityID newID = CreateEntityId(newIndex, GetEntityVersion(_entities[newIndex].mID));
			_entities[newIndex].mID = newID;
			return _entities[newIndex].mID;
		}
		_entities.push_back({ CreateEntityId(EntityIndex(_entities.size()), 0), ComponentMask() });
		return _entities.back().mID;
	}

	void Scene::DestroyEntity(EntityID id)
	{
		EntityID newID = CreateEntityId(EntityIndex(-1), GetEntityVersion(id) + 1);
		_entities[GetEntityIndex(id)].mID = newID;
		_entities[GetEntityIndex(id)].mComponentMask.reset();
		_freeEntities.push_back(GetEntityIndex(id));
	}

	void Scene::OnLoad()
	{

	}

	void Scene::OnUnload()
	{

	}
}