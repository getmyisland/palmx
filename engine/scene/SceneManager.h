#ifndef _PE_SCENE_MANAGER_H__
#define _PE_SCENE_MANAGER_H__

#include <PalmEngineSingleton.h>

#include "Scene.h"

#include <memory>

namespace PalmEngine
{
	class SceneManager : public PalmEngineSingleton<SceneManager>
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