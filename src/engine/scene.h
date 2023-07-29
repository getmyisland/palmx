#ifndef PALMX_SCENE_H
#define PALMX_SCENE_H

#include "entity.h"
#include "transform.h"
#include "../renderer/camera.h"

#include <memory>
#include <string>
#include <vector>

namespace palmx
{
	class MainCamera
	{
	public:
		MainCamera(const render::Camera* const camera, const Transform* const transform) : camera_(camera), transform_(transform) {}
		~MainCamera() {}

		glm::mat4 GetViewMatrix() const;

		const render::Camera* GetCamera() const;
		const Transform* GetTransform() const;

	private:
		MainCamera() {}

		const render::Camera* const camera_{ nullptr };
		const Transform* const transform_{ nullptr };
	};

	class Scene
	{
	public:
		std::shared_ptr<MainCamera> GetMainCamera() const;
		void SetMainCamera(const MainCamera& main_camera);

		std::vector<Entity> GetEntitiesInScene() const;
		EntityID NewEntity();
		void DestroyEntity(EntityID id);

		template<typename T>
		T* AddComponent(EntityID id)
		{
			// Ensure the has not been deleted
			if (entities_[GetEntityIndex(id)].id != id)
			{
				return nullptr;
			}

			int component_id = GetComponentId<T>();

			if (component_pools_.size() <= component_id) // Not enough component pool
			{
				component_pools_.resize(component_id + 1, nullptr);
			}
			if (component_pools_[component_id] == nullptr) // New component, make a new pool
			{
				component_pools_[component_id] = new ComponentPool(sizeof(T));
			}

			// Looks up the component in the pool, and initializes it with placement new
			T* component = new (component_pools_[component_id]->Get(GetEntityIndex(id))) T();

			// Set the bit for this component to true and return the created component
			entities_[GetEntityIndex(id)].component_mask.set(component_id);
			return component;
		}

		template<typename T>
		T* RemoveComponent(EntityID id)
		{
			// Ensure the has not been deleted
			if (entities_[GetEntityIndex(id)].id != id)
			{
				return;
			}

			int component_id = GetId<T>();
			entities_[GetEntityIndex(id)].component_mask.reset(component_id);
		}

		template<typename T>
		T* GetComponent(EntityID id)
		{
			// Ensure the has not been deleted
			if (entities_[GetEntityIndex(id)].id != id)
			{
				return nullptr;
			}

			int component_id = GetComponentId<T>();
			if (!entities_[GetEntityIndex(id)].component_mask.test(component_id))
			{
				return nullptr;
			}

			T* component = static_cast<T*>(component_pools_[component_id]->Get(GetEntityIndex(id)));
			return component;
		}

		void OnLoad();
		void OnUnload();

	private:
		std::shared_ptr<MainCamera> main_camera_;

		std::vector<Entity> entities_;
		std::vector<EntityIndex> free_entities_;
		std::vector<ComponentPool*> component_pools_;
	};
}

#endif