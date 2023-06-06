#ifndef _PE_SCENE_H__
#define _PE_SCENE_H__

#include <components/Camera.h>
#include <scene/Entity.h>

#include <string>
#include <vector>

namespace PalmEngine
{
	class Scene
	{
	public:
		Scene();
		~Scene();

	public:
		Camera* GetMainCamera();
		void SetMainCamera(Camera* mainCamera);

		std::vector<Entity> GetEntitiesInScene() const;
		EntityID NewEntity();
		void DestroyEntity(EntityID id);

		template<typename T>
		T* AddComponent(EntityID id)
		{
			// ensures you're not accessing an entity that has been deleted
			if (_entities[GetEntityIndex(id)].m_ID != id)
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
			_entities[GetEntityIndex(id)].m_ComponentMask.set(componentId);
			return pComponent;
		}

		template<typename T>
		T* RemoveComponent(EntityID id)
		{
			// ensures you're not accessing an entity that has been deleted
			if (_entities[GetEntityIndex(id)].m_ID != id)
			{
				return;
			}

			int componentId = GetId<T>();
			_entities[GetEntityIndex(id)].m_ComponentMask.reset(componentId);
		}

		template<typename T>
		T* GetComponent(EntityID id)
		{
			// ensures you're not accessing an entity that has been deleted
			if (_entities[GetEntityIndex(id)].m_ID != id)
			{
				return nullptr;
			}

			int componentId = GetComponentId<T>();
			if (!_entities[GetEntityIndex(id)].m_ComponentMask.test(componentId))
			{
				return nullptr;
			}

			T* pComponent = static_cast<T*>(_componentPools[componentId]->Get(GetEntityIndex(id)));
			return pComponent;
		}

		void OnLoad();
		void OnUnload();

	private:
		Camera* _mainCamera = nullptr;

		std::vector<Entity> _entities;
		std::vector<EntityIndex> _freeEntities;
		std::vector<ComponentPool*> _componentPools;
	};
}

#endif