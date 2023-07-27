#ifndef PALMX_ENGINE_H
#define PALMX_ENGINE_H

#include "singleton.h"
#include "scene_manager.h"
#include "input_system.h"
#include "../gui/gui_system.h"
#include "../renderer/render_system.h"
#include "../physics/physics_system.h"

#include <GLFW/glfw3.h>

#include <memory>

namespace palmx
{
	class Scene;

	struct Config
	{
		unsigned int mWidth{ 800 };
		unsigned int mHeight{ 600 };
	};

	class Engine : public Singleton<Engine>
	{
	public:
		Engine(Config& config);
		~Engine();

		static Engine& GetSingleton(void);
		static Engine* GetSingletonPtr(void);

		std::unique_ptr<gui::GuiSystem> mGuiSystem;
		std::unique_ptr<InputSystem> mInputSystem;
		std::unique_ptr<physics::PhysicsSystem> mPhysicsSystem;
		std::unique_ptr<render::RenderSystem> mRenderSystem;
		std::unique_ptr<SceneManager> mSceneManager;

		void Run(Scene& entryScene);
		void Kill();

	private:
		Engine();

		void GameLoop();
	};
}

#endif