#include "SceneModule.h"

#include "Entity.h"
#include "Logger.h"
#include "SceneView.h"
#include "ScriptHook.h"

namespace palmx
{
	SceneModule::SceneModule() { }
	SceneModule::~SceneModule() { }

	void SceneModule::StartUp()
	{
		LOG_INFO("Scene Manager initialized");
	}

	void SceneModule::ShutDown()
	{

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