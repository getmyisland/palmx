#include "Scene.h"

#include <algorithm>

namespace palmx
{
	Scene::Scene() {}
	
	Scene::~Scene() {}

	std::shared_ptr<MainCamera> Scene::GetMainCamera() const
	{
		return _mainCamera;
	}

	void Scene::SetMainCamera(const MainCamera& mainCamera)
	{
		_mainCamera = std::make_shared<MainCamera>(mainCamera);
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
			EntityID newId = CreateEntityId(newIndex, GetEntityVersion(_entities[newIndex].mId));
			_entities[newIndex].mId = newId;
			return _entities[newIndex].mId;
		}
		_entities.push_back({ CreateEntityId(EntityIndex(_entities.size()), 0), ComponentMask() });
		return _entities.back().mId;
	}

	void Scene::DestroyEntity(EntityID id)
	{
		EntityID newId = CreateEntityId(EntityIndex(-1), GetEntityVersion(id) + 1);
		_entities[GetEntityIndex(id)].mId = newId;
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