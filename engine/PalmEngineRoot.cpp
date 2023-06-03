#include "PalmEngineRoot.h"

namespace PalmEngine
{
	template<> PalmEngineRoot* PalmEngineSingleton<PalmEngineRoot>::msSingleton = 0;
	PalmEngineRoot* PalmEngineRoot::GetSingletonPtr(void)
	{
		return msSingleton;
	}
	PalmEngineRoot& PalmEngineRoot::GetSingleton(void)
	{
		return (*msSingleton);
	}

	PalmEngineRoot::PalmEngineRoot() {}

	PalmEngineRoot::PalmEngineRoot(PalmEngineConfig& palmEngineConfig)
	{
		mConfig = std::make_unique<PalmEngineConfig>(palmEngineConfig);

		mLogManager = std::make_unique<LogManager>();
		mResourceManager = std::make_unique<ResourceManager>();
		mInputManager = std::make_unique<InputManager>();
		mRenderManager = std::make_unique<RenderManager>();
		mSceneManager = std::make_unique<SceneManager>();
		mWindowManager = std::make_unique<WindowManager>();

		StartUpModules();
	}

	PalmEngine::PalmEngineRoot::~PalmEngineRoot() 
	{
		mSceneManager.release();
		mRenderManager.release();
		mInputManager.release();
		mResourceManager.release();
		mLogManager.release();
		mWindowManager.release();

		mConfig.release();
	}

	void PalmEngineRoot::StartUpModules()
	{
		mWindowManager->StartUp();
		mLogManager->StartUp();
		mResourceManager->StartUp();
		mInputManager->StartUp(mWindowManager->GetMainWindow());
		mRenderManager->StartUp();
		mSceneManager->StartUp();
	}

	void PalmEngineRoot::Run(Scene& startScene)
	{
		mSceneManager->SetActiveScene(startScene);

		GameLoop();
		ShutdownModules();
	}

	void PalmEngineRoot::GameLoop()
	{
		float deltaTime = 0.0f;	// time between current frame and last frame
		float lastFrame = 0.0f;

		while (!glfwWindowShouldClose(mWindowManager->GetMainWindow()))
		{
			float currentFrame = static_cast<float>(glfwGetTime());
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			mInputManager->CollectInput(mWindowManager->GetMainWindow());
			mSceneManager->Update(deltaTime);

			mRenderManager->Render(mWindowManager->GetMainWindow(), mSceneManager->GetActiveScene());
		}
	}

	void PalmEngineRoot::ShutdownModules()
	{
		mSceneManager->ShutDown();
		mRenderManager->ShutDown();
		mInputManager->ShutDown();
		mResourceManager->ShutDown();
		mLogManager->ShutDown();
		mWindowManager->ShutDown();
	}

	void PalmEngineRoot::Stop()
	{
		glfwSetWindowShouldClose(mWindowManager->GetMainWindow(), true);
	}
}