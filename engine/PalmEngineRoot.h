#ifndef _PALM_ENGINE_H__
#define _PALM_ENGINE_H__

#include <GLFW/glfw3.h>
#include <memory>

#include <PalmEngineConfig.h>
#include <PalmEngineSingleton.h>
#include <scene/SceneManager.h>
#include <input/InputManager.h>
#include <logging/LogManager.h>
#include <filesystem/ResourceManager.h>
#include <rendering/RenderManager.h>
#include <window/WindowManager.h>

namespace PalmEngine
{
	class PalmEngineRoot : public PalmEngineSingleton<PalmEngineRoot>
	{
	public:
		PalmEngineRoot(PalmEngineConfig& palmEngineConfig);

		static PalmEngineRoot& GetSingleton(void);
		static PalmEngineRoot* GetSingletonPtr(void);

		~PalmEngineRoot();

	private:
		PalmEngineRoot();

	public:
		std::unique_ptr<PalmEngineConfig> mConfig;

		std::unique_ptr<LogManager> mLogManager;
		std::unique_ptr<ResourceManager> mResourceManager;
		std::unique_ptr<SceneManager> mSceneManager;
		std::unique_ptr<InputManager> mInputManager;
		std::unique_ptr<RenderManager> mRenderManager;
		std::unique_ptr<WindowManager> mWindowManager;

		void Run(Scene& startScene);
		void Stop();
	
	private:
		void StartUpModules();
		void GameLoop();
		void UpdateModules(float deltaTime);
		void RenderModules();
		void ShutdownModules();
	};
}

#endif