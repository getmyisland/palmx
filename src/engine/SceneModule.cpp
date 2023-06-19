#include "SceneModule.h"

#include "Entity.h"
#include "Logger.h"
#include "SceneView.h"
#include "ScriptHook.h"

namespace palmx
{
	SceneModule::SceneModule() { }
	SceneModule::~SceneModule() { }

	void SceneModule::Start()
	{
		LOG_INFO("Scene Module started");
	}

	void SceneModule::Stop()
	{
		LOG_INFO("Scene Module stopped");
	}

	void SceneModule::Update(float deltaTime)
	{
		for (EntityID ent : SceneView<ScriptHook>(*GetActiveScene()))
		{
			for (auto& scriptBehavior : GetActiveScene()->GetComponent<ScriptHook>(ent)->GetScriptBehavior())
			{
				scriptBehavior->Update(ent, deltaTime);
			}
		}
	}

	Scene* SceneModule::GetActiveScene() const
	{
		return _activeScene.get();
	}

	void SceneModule::SetActiveScene(Scene& scene)
	{
		if (_activeScene != nullptr)
		{
			_activeScene->OnUnload();
		}

		_activeScene.reset(&scene);
		_activeScene->OnLoad();
	}
}