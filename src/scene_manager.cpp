#include <palmx/scene_manager.h>

#include <palmx/entity.h>
#include <palmx/logger.h>
#include <palmx/scene_view.h>
#include <palmx/script_hook.h>

namespace palmx
{
	SceneManager::SceneManager() { }
	SceneManager::~SceneManager() { }

	void SceneManager::Update(float delta_time)
	{
		for (EntityID ent : SceneView<ScriptHook>(*GetActiveScene()))
		{
			for (auto& script_behavior : GetActiveScene()->GetComponent<ScriptHook>(ent)->GetScriptBehavior())
			{
				script_behavior->Update(ent, delta_time);
			}
		}
	}

	Scene* SceneManager::GetActiveScene() const
	{
		return active_scene_.get();
	}

	void SceneManager::SetActiveScene(Scene& scene)
	{
		if (active_scene_ != nullptr)
		{
			active_scene_->OnUnload();
		}

		active_scene_.reset(&scene);
		active_scene_->OnLoad();
	}
}