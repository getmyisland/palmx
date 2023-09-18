#ifndef PALMX_ENGINE_H
#define PALMX_ENGINE_H

#include <palmx/singleton.h>

#include <GLFW/glfw3.h>

#include <memory>

namespace palmx
{
	namespace gui
	{
		class GuiSystem;
	}

	namespace render
	{
		class RenderSystem;
	}

	namespace physics
	{
		class PhysicsSystem;
	}

	class Scene;
	class SceneManager;
	class InputSystem;

	struct Config
	{
		unsigned int window_width{ 800 };
		unsigned int window_height{ 600 };
	};

	class Engine : public Singleton<Engine>
	{
	public:
		Engine(Config& config);
		~Engine();

		static Engine& GetSingleton(void);
		static Engine* GetSingletonPtr(void);

		std::unique_ptr<gui::GuiSystem> gui_system;
		std::unique_ptr<InputSystem> input_system;
		std::unique_ptr<physics::PhysicsSystem> physics_system;
		std::unique_ptr<render::RenderSystem> render_system;

		Scene* GetActiveScene() const;
		void SetActiveScene(Scene& scene);

		void Run(Scene& entry_scene);
		void Kill();

	private:
		Engine();

		std::unique_ptr<Scene> active_scene_;

		void Loop();
	};
}

#endif