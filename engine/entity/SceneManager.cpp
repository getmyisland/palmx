#include "SceneManager.h"

#include <logging/LogManager.h>
#include <entity/ScriptHook.h>
#include <entity/SceneView.h>

namespace palmx
{
	SceneManager::SceneManager() { }
	SceneManager::~SceneManager() { }

	template<> SceneManager* Singleton<SceneManager>::msSingleton = 0;
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
		DEBUG_LOG_INFO("Scene Manager initialized");
	}

	void SceneManager::ShutDown()
	{

	}

	void SceneManager::Update(float deltaTime)
	{
		for (EntityID ent : SceneView<ScriptHook>(*GetActiveScene()))
		{
			for (auto& scriptBehavior : GetActiveScene()->GetComponent<ScriptHook>(ent)->GetScriptBehavior())
			{
				scriptBehavior->Update(ent, deltaTime);
			}
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