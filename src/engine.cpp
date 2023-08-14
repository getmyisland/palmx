#include <palmx/engine.h>

#include <palmx/scene_manager.h>
#include <palmx/input_system.h>
#include <palmx/gui_system.h>
#include <palmx/render_system.h>
#include <palmx/physics_system.h>

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
		gui_system->Start(config.width, config.height);

		input_system = std::make_unique<InputSystem>();
		input_system->Start(gui_system->GetMainWindow());

		render_system = std::make_unique<render::RenderSystem>();
		render_system->Start();

		scene_manager = std::make_unique<SceneManager>();
	}

	palmx::Engine::~Engine()
	{
		scene_manager.release();
		physics_system.release();
		render_system.release();
		input_system.release();
		gui_system.release();
	}

	void Engine::Run(Scene& entry_scene)
	{
		scene_manager->SetActiveScene(entry_scene);

		GameLoop();

		render_system->Stop();
		input_system->Stop();
		gui_system->Stop();
	}

	void Engine::GameLoop()
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
				physics_system->Step(delta_time, scene_manager->GetActiveScene());
			}

			// First collect the input
			input_system->CollectInput(gui_system->GetMainWindow());

			// Then update all entities in the scene
			scene_manager->Update(delta_time);

			// Now render the scene
			render_system->Render(gui_system->GetMainWindow(), scene_manager->GetActiveScene());
		}
	}

	void Engine::Kill()
	{
		glfwSetWindowShouldClose(gui_system->GetMainWindow(), true);
	}
}