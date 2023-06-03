#include "SceneManager.h"

#include <logging/LogManager.h>

namespace PalmEngine
{
	SceneManager::SceneManager() { }
	SceneManager::~SceneManager() { }

	template<> SceneManager* PalmEngineSingleton<SceneManager>::msSingleton = 0;
	SceneManager* SceneManager::GetSingletonPtr(void)
	{
		return msSingleton;
	}
	SceneManager& SceneManager::GetSingleton(void)
	{
		return (*msSingleton);
	}

	void SceneManager::StartUp()
	{
		PE_LOG_MANAGER->LogInfo("Scene Manager initialized");
	}

	void SceneManager::ShutDown()
	{

	}

	void SceneManager::Update(float deltaTime)
	{
		for (auto& entity : GetActiveScene()->GetEntitiesInScene())
		{
			entity->Update(deltaTime);
		}
	}

	Scene* SceneManager::GetActiveScene() const
	{
		return _activeScene.get();
	}

	void SceneManager::SetActiveScene(Scene& scene)
	{
		if (_activeScene != nullptr)
		{
			_activeScene->OnUnload();
		}

		_activeScene.reset(&scene);
		_activeScene->OnLoad();
	}
}