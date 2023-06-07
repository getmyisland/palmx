#ifndef _PALM_ENGINE_ROOT_H__
#define _PALM_ENGINE_ROOT_H__

#include <GLFW/glfw3.h>
#include <memory>

#include <filesystem/ResourceManager.h>
#include <input/InputManager.h>
#include <logging/LogManager.h>
#include <PalmEngineConfig.h>
#include <PalmEngineSingleton.h>
#include <rendering/RenderManager.h>
#include <scene/SceneManager.h>
#include <window/WindowManager.h>

namespace PalmEngine
{
	class PalmEngineRoot : public PalmEngineSingleton<PalmEngineRoot>
	{
	public:
		PalmEngineRoot(PalmEngineConfig& palmEngineConfig);
		~PalmEngineRoot();

		static PalmEngineRoot& GetSingleton(void);
		static PalmEngineRoot* GetSingletonPtr(void);

		std::unique_ptr<PalmEngineConfig> m_pConfig;

		std::unique_ptr<LogManager> m_pLogManager;
		std::unique_ptr<ResourceManager> m_pResourceManager;
		std::unique_ptr<SceneManager> m_pSceneManager;
		std::unique_ptr<InputManager> m_pInputManager;
		std::unique_ptr<RenderManager> m_pRenderManager;
		std::unique_ptr<WindowManager> m_pWindowManager;

		void Run(Scene& startScene);
		void Stop();
	
	private:
		PalmEngineRoot();

		void StartUpModules();
		void GameLoop();
		void ShutdownModules();
	};
}

#endif