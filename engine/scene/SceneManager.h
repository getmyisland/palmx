#ifndef _PE_ENTITY_MANAGER_H__
#define _PE_ENTITY_MANAGER_H__

#include <PalmEngineSingleton.h>
#include <PalmEngineManager.h>

#include "Scene.h"

#include <memory>

namespace PalmEngine
{
	class SceneManager : PalmEngineManager, public PalmEngineSingleton<SceneManager>
	{
	public:
		SceneManager();
		~SceneManager();

		static SceneManager& GetSingleton(void);
		static SceneManager* GetSingletonPtr(void);

		virtual void StartUp() override;
		virtual void ShutDown() override;

	public:
		Scene* GetActiveScene() const;
		void SetActiveScene(Scene& scene);

	private:
		std::unique_ptr<Scene> _activeScene;
	};
}

#endif