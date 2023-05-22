#ifndef _PALM_ENGINE_H__
#define _PALM_ENGINE_H__

#include <GLFW/glfw3.h>
#include <memory>

#include <PalmEngineConfig.h>
#include <PalmEngineSingleton.h>
#include <entity/EntityManager.h>
#include <input/InputManager.h>
#include <logging/LogManager.h>
#include <filesystem/ResourceManager.h>
#include <rendering/RenderManager.h>

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
		std::unique_ptr<LogManager> mLogManager;
		std::unique_ptr<ResourceManager> mResourceManager;
		std::unique_ptr<EntityManager> mEntityManager;
		std::unique_ptr<InputManager> mInputManager;
		std::unique_ptr<RenderManager> mRenderManager;

		void KillGameLoop();
	
	private:
		GLFWwindow* _window = nullptr;

		void StartUpModules();
		void GameLoop();
		void UpdateModules();
		void RenderModules();
		void ShutdownModules();
	};
}

#endif