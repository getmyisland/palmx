#ifndef PALMX_SCENE_MANAGER_H
#define PALMX_SCENE_MANAGER_H

#include "scene.h"

#include <memory>

namespace palmx
{
	class SceneManager
	{
	public:
		SceneManager();
		~SceneManager();

		void Update(float deltaTime);

	public:
		Scene* GetActiveScene() const;
		void SetActiveScene(Scene& scene);

	private:
		std::unique_ptr<Scene> _activeScene;
	};
}

#endif