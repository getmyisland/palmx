#ifndef PALMX_ENGINE_H_
#define PALMX_ENGINE_H_

#include "Singleton.h"
#include "SceneManager.h"
#include "InputSystem.h"
#include "../gui/GuiSystem.h"
#include "../renderer/RenderSystem.h"

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

		std::unique_ptr<GuiSystem> mGuiSystem;
		std::unique_ptr<InputSystem> mInputSystem;
		std::unique_ptr<RenderSystem> mRenderSystem;
		std::unique_ptr<SceneManager> mSceneManager;

		void Run(Scene& entryScene);
		void Kill();

	private:
		Engine();

		void GameLoop();
	};
}

#endif