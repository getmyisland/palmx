#ifndef PALMX_SCENE_VIEW_H
#define PALMX_SCENE_VIEW_H

#include "entity.h"
#include "scene.h"

namespace palmx
{
	template<typename... ComponentTypes>
	struct SceneView
	{
		SceneView(Scene& scene) : mScene(&scene)
		{
			if (sizeof...(ComponentTypes) == 0)
			{
				mAll = true;
			}
			else
			{
				// Unpack the template parameters into an initializer list
				int componentIds[] = { 0, GetComponentId<ComponentTypes>() ... };
				for (int i = 1; i < (sizeof...(ComponentTypes) + 1); i++)
				{
					mComponentMask.set(componentIds[i]);
				}
			}
		}

		struct Iterator
		{
			Iterator(Scene* scene, EntityIndex index, ComponentMask mask, bool all)
				: mScene(scene), mIndex(index), mComponentMask(mask), mAll(all) {}

			EntityID operator*() const
			{
				return mScene->GetEntitiesInScene()[mIndex].mId;
			}

			bool operator==(const Iterator& other) const
			{
				return mIndex == other.mIndex || mIndex == mScene->GetEntitiesInScene().size();
			}

			bool operator!=(const Iterator& other) const
			{
				return mIndex != other.mIndex && mIndex != mScene->GetEntitiesInScene().size();
			}

			bool ValidIndex()
			{
				return
					// It's a valid entity ID
					IsEntityValid(mScene->GetEntitiesInScene()[mIndex].mId) &&
					// It has the correct component mask
					(mAll || mComponentMask == (mComponentMask & mScene->GetEntitiesInScene()[mIndex].mComponentMask));
			}

			Iterator& operator++()
			{
				do
				{
					mIndex++;
				} while (mIndex < mScene->GetEntitiesInScene().size() && !ValidIndex());
				return *this;
			}

			EntityIndex mIndex;
			Scene* mScene;
			ComponentMask mComponentMask;
			bool mAll{ false };
		};

		const Iterator begin() const
		{
			int firstIndex = 0;
			while (firstIndex < mScene->GetEntitiesInScene().size() &&
				(mComponentMask != (mComponentMask & mScene->GetEntitiesInScene()[firstIndex].mComponentMask)
					|| !IsEntityValid(mScene->GetEntitiesInScene()[firstIndex].mId)))
			{
				firstIndex++;
			}
			return Iterator(mScene, firstIndex, mComponentMask, mAll);
		}

		const Iterator end() const
		{
			return Iterator(mScene, EntityIndex(mScene->GetEntitiesInScene().size()), mComponentMask, mAll);
		}

		Scene* mScene{ nullptr };
		ComponentMask mComponentMask;
		bool mAll{ false };
	};
}

#endif