#ifndef PALMX_ENGINE_H
#define PALMX_ENGINE_H

#include "singleton.h"

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