#include "scene_manager.h"

#include "entity.h"
#include "logger.h"
#include "scene_view.h"
#include "script_hook.h"

namespace palmx
{
	SceneManager::SceneManager() { }
	SceneManager::~SceneManager() { }

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