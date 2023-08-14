#include <palmx/scene.h>

#include <algorithm>

namespace palmx
{
	glm::mat4 MainCamera::GetViewMatrix() const
	{
		return glm::lookAt(transform_->GetPosition(), transform_->GetPosition() + transform_->GetForward(), transform_->GetUp());
	}

	const render::Camera* MainCamera::GetCamera() const
	{
		return camera_;
	}

	const Transform* MainCamera::GetTransform() const
	{
		return transform_;
	}

	std::shared_ptr<MainCamera> Scene::GetMainCamera() const
	{
		return main_camera_;
	}

	void Scene::SetMainCamera(const MainCamera& main_camera)
	{
		main_camera_ = std::make_shared<MainCamera>(main_camera);
	}

	std::vector<Entity> Scene::GetEntitiesInScene() const
	{
		return entities_;
	}

	EntityID Scene::NewEntity()
	{
		if (!free_entities_.empty())
		{
			EntityIndex new_index = free_entities_.back();
			free_entities_.pop_back();
			EntityID new_id = CreateEntityId(new_index, GetEntityVersion(entities_[new_index].id));
			entities_[new_index].id = new_id;
			return entities_[new_index].id;
		}
		entities_.push_back({ CreateEntityId(EntityIndex(entities_.size()), 0), ComponentMask() });
		return entities_.back().id;
	}

	void Scene::DestroyEntity(EntityID id)
	{
		EntityID new_id = CreateEntityId(EntityIndex(-1), GetEntityVersion(id) + 1);
		entities_[GetEntityIndex(id)].id = new_id;
		entities_[GetEntityIndex(id)].component_mask.reset();
		free_entities_.push_back(GetEntityIndex(id));
	}

	void Scene::OnLoad()
	{

	}

	void Scene::OnUnload()
	{

	}
}