#include "PalmEngineRoot.h"

namespace PalmEngine
{
	template<> PalmEngineRoot* PalmEngineSingleton<PalmEngineRoot>::ms_Singleton = 0;
	PalmEngineRoot* PalmEngineRoot::GetSingletonPtr(void)
	{
		return ms_Singleton;
	}
	PalmEngineRoot& PalmEngineRoot::GetSingleton(void)
	{
		return (*ms_Singleton);
	}

	PalmEngineRoot::PalmEngineRoot() {}

	PalmEngineRoot::PalmEngineRoot(PalmEngineConfig& palmEngineConfig)
	{
		m_pConfig = std::make_unique<PalmEngineConfig>(palmEngineConfig);

		m_pLogManager = std::make_unique<LogManager>();
		m_pResourceManager = std::make_unique<ResourceManager>();
		m_pInputManager = std::make_unique<InputManager>();
		m_pRenderManager = std::make_unique<RenderManager>();
		m_pSceneManager = std::make_unique<SceneManager>();
		m_pWindowManager = std::make_unique<WindowManager>();

		StartUpModules();
	}

	PalmEngine::PalmEngineRoot::~PalmEngineRoot() 
	{
		m_pSceneManager.release();
		m_pRenderManager.release();
		m_pInputManager.release();
		m_pResourceManager.release();
		m_pLogManager.release();
		m_pWindowManager.release();

		m_pConfig.release();
	}

	void PalmEngineRoot::StartUpModules()
	{
		m_pWindowManager->StartUp();
		m_pLogManager->StartUp();
		m_pResourceManager->StartUp();
		m_pInputManager->StartUp(m_pWindowManager->GetMainWindow());
		m_pRenderManager->StartUp();
		m_pSceneManager->StartUp();
	}

	void PalmEngineRoot::Run(Scene& startScene)
	{
		m_pSceneManager->SetActiveScene(startScene);

		GameLoop();
		ShutdownModules();
	}

	void PalmEngineRoot::GameLoop()
	{
		float deltaTime = 0.0f;	// time between current frame and last frame
		float lastFrame = 0.0f;

		while (!glfwWindowShouldClose(m_pWindowManager->GetMainWindow()))
		{
			float currentFrame = static_cast<float>(glfwGetTime());
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			m_pInputManager->CollectInput(m_pWindowManager->GetMainWindow());
			m_pSceneManager->Update(deltaTime);

			m_pRenderManager->Render(m_pWindowManager->GetMainWindow(), m_pSceneManager->GetActiveScene());
		}
	}

	void PalmEngineRoot::ShutdownModules()
	{
		m_pSceneManager->ShutDown();
		m_pRenderManager->ShutDown();
		m_pInputManager->ShutDown();
		m_pResourceManager->ShutDown();
		m_pLogManager->ShutDown();
		m_pWindowManager->ShutDown();
	}

	void PalmEngineRoot::Stop()
	{
		glfwSetWindowShouldClose(m_pWindowManager->GetMainWindow(), true);
	}
}