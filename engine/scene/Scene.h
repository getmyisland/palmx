#ifndef _PE_SCENE_H__
#define _PE_SCENE_H__

#include "Entity.h"

#include <vector>

namespace PalmEngine
{
	class Scene
	{
	public:
		Scene();
		~Scene();

	public:
		std::vector<Entity> mEntitiesInScene;

		void OnLoad();
		void OnUnload();
	};
}

#endif