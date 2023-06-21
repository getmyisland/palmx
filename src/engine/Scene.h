#ifndef PALMX_SCENE_H_
#define PALMX_SCENE_H_

#include "Entity.h"
#include "Transform.h"
#include "../renderer/Camera.h"

#include <memory>
#include <string>
#include <vector>

namespace palmx
{
	struct MainCamera
	{
	public:
		MainCamera(const Camera* const camera, const Transform* const transform) : mCamera(camera), mTransform(transform) {}
		~MainCamera() {}

		glm::mat4 GetViewMatrix() const;

		const Camera* const mCamera{ nullptr };
		const Transform* const mTransform{ nullptr };

	private:
		MainCamera() {}
	};

	class Scene
	{
	public:
		std::shared_ptr<MainCamera> GetMainCamera() const;
		void SetMainCamera(const MainCamera& mainCamera);

		std::vector<Entity> GetEntitiesInScene() const;
		EntityID NewEntity();
		void DestroyEntity(EntityID id);

		template<typename T>
		T* AddComponent(EntityID id)
		{
			// Ensure the has not been deleted
			if (_entities[GetEntityIndex(id)].mId != id)
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
			T* component = new (_componentPools[componentId]->Get(GetEntityIndex(id))) T();

			// Set the bit for this component to true and return the created component
			_entities[GetEntityIndex(id)].mComponentMask.set(componentId);
			return component;
		}

		template<typename T>
		T* RemoveComponent(EntityID id)
		{
			// Ensure the has not been deleted
			if (_entities[GetEntityIndex(id)].mId != id)
			{
				return;
			}

			int componentId = GetId<T>();
			_entities[GetEntityIndex(id)].mComponentMask.reset(componentId);
		}

		template<typename T>
		T* GetComponent(EntityID id)
		{
			// Ensure the has not been deleted
			if (_entities[GetEntityIndex(id)].mId != id)
			{
				return nullptr;
			}

			int componentId = GetComponentId<T>();
			if (!_entities[GetEntityIndex(id)].mComponentMask.test(componentId))
			{
				return nullptr;
			}

			T* component = static_cast<T*>(_componentPools[componentId]->Get(GetEntityIndex(id)));
			return component;
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