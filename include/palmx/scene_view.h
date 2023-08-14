#ifndef PALMX_SCENE_VIEW_H
#define PALMX_SCENE_VIEW_H

#include <palmx/entity.h>
#include <palmx/scene.h>

namespace palmx
{
	template<typename... ComponentTypes>
	class SceneView
	{
	public:
		SceneView(Scene& scene) : scene_(&scene)
		{
			if (sizeof...(ComponentTypes) == 0)
			{
				all_ = true;
			}
			else
			{
				// Unpack the template parameters into an initializer list
				int component_ids[] = { 0, GetComponentId<ComponentTypes>() ... };
				for (int i = 1; i < (sizeof...(ComponentTypes) + 1); i++)
				{
					component_mask_.set(component_ids[i]);
				}
			}
		}

		class Iterator
		{
		public:
			Iterator(Scene* scene, EntityIndex index, ComponentMask mask, bool all)
				: scene_(scene), index_(index), component_mask_(mask), all_(all) {}

			EntityID operator*() const
			{
				return scene_->GetEntitiesInScene()[index_].id;
			}

			bool operator==(const Iterator& other) const
			{
				return index_ == other.index_ || index_ == scene_->GetEntitiesInScene().size();
			}

			bool operator!=(const Iterator& other) const
			{
				return index_ != other.index_ && index_ != scene_->GetEntitiesInScene().size();
			}

			bool ValidIndex()
			{
				return
					// It's a valid entity ID
					IsEntityValid(scene_->GetEntitiesInScene()[index_].id) &&
					// It has the correct component mask
					(all_ || component_mask_ == (component_mask_ & scene_->GetEntitiesInScene()[index_].component_mask));
			}

			Iterator& operator++()
			{
				do
				{
					index_++;
				} while (index_ < scene_->GetEntitiesInScene().size() && !ValidIndex());
				return *this;
			}

			EntityIndex index_;
			Scene* scene_;
			ComponentMask component_mask_;
			bool all_{ false };
		};

		const Iterator begin() const
		{
			int first_index = 0;
			while (first_index < scene_->GetEntitiesInScene().size() &&
				(component_mask_ != (component_mask_ & scene_->GetEntitiesInScene()[first_index].component_mask)
					|| !IsEntityValid(scene_->GetEntitiesInScene()[first_index].id)))
			{
				first_index++;
			}
			return Iterator(scene_, first_index, component_mask_, all_);
		}

		const Iterator end() const
		{
			return Iterator(scene_, EntityIndex(scene_->GetEntitiesInScene().size()), component_mask_, all_);
		}

	private:
		Scene* scene_{ nullptr };
		ComponentMask component_mask_;
		bool all_{ false };
	};
}

#endif