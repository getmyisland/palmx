#ifndef PALMX_ROOT_H_
#define PALMX_ROOT_H_

#include <GLFW/glfw3.h>
#include <memory>

#include <Config.h>
#include <Singleton.h>

#include <entity/SceneManager.h>
#include <gui/WindowManager.h>
#include <input/InputManager.h>
#include <utility/LogManager.h>
#include <utility/ResourceManager.h>
#include <rendering/RenderManager.h>

namespace palmx
{
	class Root : public Singleton<Root>
	{
	public:
		Root(Config& config);
		~Root();

		static Root& GetSingleton(void);
		static Root* GetSingletonPtr(void);

		std::unique_ptr<Config> mConfig;

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

		void StartModules();
		void GameLoop();
		void ShutdownModules();
	};
}

#endif