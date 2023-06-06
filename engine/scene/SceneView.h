#ifndef _PE_SCENE_VIEW_H__
#define _PE_SCENE_VIEW_H__

#include <scene/Entity.h>
#include <scene/Scene.h>

namespace PalmEngine
{
	template<typename... ComponentTypes>
	struct SceneView
	{
		SceneView(Scene& scene) : m_pScene(&scene)
		{
			if (sizeof...(ComponentTypes) == 0)
			{
				m_All = true;
			}
			else
			{
				// Unpack the template parameters into an initializer list
				int componentIds[] = { 0, GetComponentId<ComponentTypes>() ... };
				for (int i = 1; i < (sizeof...(ComponentTypes) + 1); i++)
				{
					m_ComponentMask.set(componentIds[i]);
				}
			}
		}

		struct Iterator
		{
			Iterator(Scene* pScene, EntityIndex index, ComponentMask mask, bool all)
				: m_pScene(pScene), m_Index(index), m_ComponentMask(mask), m_All(all) {}

			EntityID operator*() const
			{
				return m_pScene->GetEntitiesInScene()[m_Index].m_ID;
			}

			bool operator==(const Iterator& other) const
			{
				return m_Index == other.m_Index || m_Index == m_pScene->GetEntitiesInScene().size();
			}

			bool operator!=(const Iterator& other) const
			{
				return m_Index != other.m_Index && m_Index != m_pScene->GetEntitiesInScene().size();
			}

			bool ValidIndex()
			{
				return
					// It's a valid entity ID
					IsEntityValid(m_pScene->GetEntitiesInScene()[m_Index].m_ID) &&
					// It has the correct component mask
					(m_All || m_ComponentMask == (m_ComponentMask & m_pScene->GetEntitiesInScene()[m_Index].m_ComponentMask));
			}

			Iterator& operator++()
			{
				do
				{
					m_Index++;
				} while (m_Index < m_pScene->GetEntitiesInScene().size() && !ValidIndex());
				return *this;
			}

			EntityIndex m_Index;
			Scene* m_pScene;
			ComponentMask m_ComponentMask;
			bool m_All{ false };
		};

		const Iterator begin() const
		{
			int firstIndex = 0;
			while (firstIndex < m_pScene->GetEntitiesInScene().size() &&
				(m_ComponentMask != (m_ComponentMask & m_pScene->GetEntitiesInScene()[firstIndex].m_ComponentMask)
					|| !IsEntityValid(m_pScene->GetEntitiesInScene()[firstIndex].m_ID)))
			{
				firstIndex++;
			}
			return Iterator(m_pScene, firstIndex, m_ComponentMask, m_All);
		}

		const Iterator end() const
		{
			return Iterator(m_pScene, EntityIndex(m_pScene->GetEntitiesInScene().size()), m_ComponentMask, m_All);
		}

		Scene* m_pScene{ nullptr };
		ComponentMask m_ComponentMask;
		bool m_All{ false };
	};
}

#endif