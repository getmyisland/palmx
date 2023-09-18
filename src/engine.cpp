#include <palmx/engine.h>

#include "input_system.h"
#include "gui_system.h"
#include "physics_system.h"
#include "render_system.h"

#include <palmx/scene.h>
#include <palmx/scene_view.h>
#include <palmx/script_hook.h>

namespace palmx
{
	template<> Engine* Singleton<Engine>::singleton_ = 0;
	Engine* Engine::GetSingletonPtr(void)
	{
		return singleton_;
	}
	Engine& Engine::GetSingleton(void)
	{
		return (*singleton_);
	}

	Engine::Engine() {}

	Engine::Engine(Config& config)
	{
		gui_system = std::make_unique<gui::GuiSystem>();
		gui_system->Start(config.window_width, config.window_height);

		input_system = std::make_unique<InputSystem>();
		input_system->Start(gui_system->GetMainWindow());

		render_system = std::make_unique<render::RenderSystem>();
		render_system->Start();
	}

	Engine::~Engine()
	{
		active_scene_.release();

		physics_system.release();
		render_system.release();
		input_system.release();
		gui_system.release();
	}

	Scene* Engine::GetActiveScene() const
	{
		return active_scene_.get();
	}

	void Engine::SetActiveScene(Scene& scene)
	{
		if (active_scene_ != nullptr)
		{
			active_scene_->OnUnload();
		}

		active_scene_.reset(&scene);
		active_scene_->OnLoad();
	}

	void Engine::Run(Scene& entry_scene)
	{
		SetActiveScene(entry_scene);

		Loop();

		render_system->Stop();
		input_system->Stop();
		gui_system->Stop();
	}

	void Engine::Loop()
	{
		float delta_time = 0.0f;	// time between current frame and last frame
		float last_frame = 0.0f;

		const float physics_timestep = 0.02f;
		float fixed_delta_time = 0.0f;

		while (!glfwWindowShouldClose(gui_system->GetMainWindow()))
		{
			float current_frame = static_cast<float>(glfwGetTime());
			delta_time = current_frame - last_frame;
			last_frame = current_frame;

			fixed_delta_time += delta_time;
			if (fixed_delta_time >= physics_timestep)
			{
				fixed_delta_time = 0;
				physics_system->Step(delta_time, GetActiveScene());
			}

			input_system->CollectInput(gui_system->GetMainWindow());

			for (EntityID ent : SceneView<ScriptHook>(*GetActiveScene()))
			{
				for (auto& script_behavior : GetActiveScene()->GetComponent<ScriptHook>(ent)->GetScriptBehavior())
				{
					script_behavior->Update(ent, delta_time);
				}
			}

			render_system->Render(gui_system->GetMainWindow(), GetActiveScene());
		}
	}

	void Engine::Kill()
	{
		glfwSetWindowShouldClose(gui_system->GetMainWindow(), true);
	}
}