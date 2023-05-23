#include "SceneManager.h"

namespace PalmEngine
{
	SceneManager::SceneManager() { }
	SceneManager::~SceneManager() { }

	//-----------------------------------------------------------------------

	template<> SceneManager* PalmEngineSingleton<SceneManager>::msSingleton = 0;
	SceneManager* SceneManager::GetSingletonPtr(void)
	{
		return msSingleton;
	}
	SceneManager& SceneManager::GetSingleton(void)
	{
		return (*msSingleton);
	}

	//-----------------------------------------------------------------------

	void SceneManager::StartUp()
	{

	}

	void SceneManager::ShutDown()
	{

	}

	//-----------------------------------------------------------------------

	Scene* SceneManager::GetActiveScene()
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