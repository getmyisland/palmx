#ifndef PALMX_SCENE_MODULE_H_
#define PALMX_SCENE_MODULE_H_

#include "Scene.h"

#include <memory>

namespace palmx
{
	class SceneModule
	{
	public:
		SceneModule();
		~SceneModule();

		void StartUp();
		void ShutDown();

		void Update(float deltaTime);

	public:
		Scene* GetActiveScene() const;
		void SetActiveScene(Scene& scene);

	private:
		std::unique_ptr<Scene> _activeScene;
	};
}

#endif