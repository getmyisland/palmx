#ifndef PALMX_SCENE_H_
#define PALMX_SCENE_H_

#include <entity/Camera.h>
#include <entity/Entity.h>
#include <entity/Transform.h>

#include <memory>
#include <string>
#include <vector>

namespace palmx
{
	class Scene
	{
	public:
		Scene();
		~Scene();

	public:
		std::shared_ptr<MainCamera> GetMainCamera() const;
		void SetMainCamera(const MainCamera& mainCamera);

		std::vector<Entity> GetEntitiesInScene() const;
		EntityID NewEntity();
		void DestroyEntity(EntityID id);

		template<typename T>
		T* AddComponent(EntityID id)
		{
			// ensures you're not accessing an entity that has been deleted
			if (_entities[GetEntityIndex(id)].mID != id)
			{
				return nullptr;
			}

			int componentId = GetComponentId<T>();

			if (_componentPools.size() <= componentId) // Not enough component pool
			{
				_componentPools.resize(componentId + 1, nullptr);
			}
			if (_componentPools[componentId] == nullptr) // New component, make a new pool
			{
				_componentPools[componentId] = new ComponentPool(sizeof(T));
			}

			// Looks up the component in the pool, and initializes it with placement new
			T* pComponent = new (_componentPools[componentId]->Get(GetEntityIndex(id))) T();

			// Set the bit for this component to true and return the created component
			_entities[GetEntityIndex(id)].mComponentMask.set(componentId);
			return pComponent;
		}

		template<typename T>
		T* RemoveComponent(EntityID id)
		{
			// ensures you're not accessing an entity that has been deleted
			if (_entities[GetEntityIndex(id)].mID != id)
			{
				return;
			}

			int componentId = GetId<T>();
			_entities[GetEntityIndex(id)].mComponentMask.reset(componentId);
		}

		template<typename T>
		T* GetComponent(EntityID id)
		{
			// ensures you're not accessing an entity that has been deleted
			if (_entities[GetEntityIndex(id)].mID != id)
			{
				return nullptr;
			}

			int componentId = GetComponentId<T>();
			if (!_entities[GetEntityIndex(id)].mComponentMask.test(componentId))
			{
				return nullptr;
			}

			T* pComponent = static_cast<T*>(_componentPools[componentId]->Get(GetEntityIndex(id)));
			return pComponent;
		}

		void OnLoad();
		void OnUnload();

	private:
		std::shared_ptr<MainCamera> _mainCamera;

		std::vector<Entity> _entities;
		std::vector<EntityIndex> _freeEntities;
		std::vector<ComponentPool*> _componentPools;
	};
}

#endif