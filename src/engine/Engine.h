#ifndef PALMX_ENGINE_H_
#define PALMX_ENGINE_H_

#include "Singleton.h"
#include "InputModule.h"
#include "SceneModule.h"
#include "../gui/GuiModule.h"
#include "../renderer/RenderModule.h"

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

		std::unique_ptr<GuiModule> mWindowModule;
		std::unique_ptr<InputModule> mInputModule;
		std::unique_ptr<RenderModule> mRenderModule;
		std::unique_ptr<SceneModule> mSceneModule;

		void Run(Scene& entryScene);
		void Kill();

	private:
		Engine();

		void GameLoop();
	};
}

#endif