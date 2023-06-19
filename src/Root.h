#ifndef PALMX_ROOT_H_
#define PALMX_ROOT_H_

#include <Singleton.h>

#include <logging/LogManager.h>
#include <entity/SceneManager.h>
#include <filesystem/ResourceManager.h>
#include <gui/WindowManager.h>
#include <input/InputManager.h>
#include <rendering/RenderManager.h>

#include <GLFW/glfw3.h>

#include <memory>

namespace palmx
{
	struct Config
	{
		unsigned int mWidth{ 800 };
		unsigned int mHeight{ 600 };
	};

	class Root : public Singleton<Root>
	{
	public:
		Root(Config& config);
		~Root();

		static Root& GetSingleton(void);
		static Root* GetSingletonPtr(void);

		std::unique_ptr<LogManager> mLogManager;
		std::unique_ptr<ResourceManager> mResourceManager;
		std::unique_ptr<SceneManager> mSceneManager;
		std::unique_ptr<InputManager> mInputManager;
		std::unique_ptr<RenderManager> mRenderManager;
		std::unique_ptr<WindowManager> mWindowManager;

		void Run(Scene& entryScene);
		void Kill();

	private:
		Root();

		void GameLoop();
	};
}

#endif