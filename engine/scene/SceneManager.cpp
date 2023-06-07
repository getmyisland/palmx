#include "SceneManager.h"

#include <logging/LogManager.h>
#include <scene/components/ScriptHook.h>
#include <scene/SceneView.h>

namespace PalmEngine
{
	SceneManager::SceneManager() { }
	SceneManager::~SceneManager() { }

	template<> SceneManager* PalmEngineSingleton<SceneManager>::ms_Singleton = 0;
	SceneManager* SceneManager::GetSingletonPtr(void)
	{
		return ms_Singleton;
	}
	SceneManager& SceneManager::GetSingleton(void)
	{
		return (*ms_Singleton);
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