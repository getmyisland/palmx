#include "Scene.h"

#include <algorithm>

namespace PalmEngine
{
	Scene::Scene() {}

	Scene::~Scene() {}

	Camera* Scene::GetMainCamera()
	{
		return _mainCamera;
	}

	void Scene::SetMainCamera(Camera* mainCamera)
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
			EntityID newID = CreateEntityId(newIndex, GetEntityVersion(_entities[newIndex].m_ID));
			_entities[newIndex].m_ID = newID;
			return _entities[newIndex].m_ID;
		}
		_entities.push_back({ CreateEntityId(EntityIndex(_entities.size()), 0), ComponentMask() });
		return _entities.back().m_ID;
	}

	void Scene::DestroyEntity(EntityID id)
	{
		EntityID newID = CreateEntityId(EntityIndex(-1), GetEntityVersion(id) + 1);
		_entities[GetEntityIndex(id)].m_ID = newID;
		_entities[GetEntityIndex(id)].m_ComponentMask.reset();
		_freeEntities.push_back(GetEntityIndex(id));
	}

	void Scene::OnLoad()
	{

	}

	void Scene::OnUnload()
	{

	}
}