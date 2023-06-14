#ifndef PALMX_SCENE_MANAGER_H_
#define PALMX_SCENE_MANAGER_H_

#include <Singleton.h>

#include "Scene.h"

#include <memory>

namespace palmx
{
	class SceneManager : public Singleton<SceneManager>
	{
	public:
		SceneManager();
		~SceneManager();

		static SceneManager& GetSingleton(void);
		static SceneManager* GetSingletonPtr(void);

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