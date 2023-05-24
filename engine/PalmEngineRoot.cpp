#include "PalmEngineRoot.h"

namespace PalmEngine
{
	//-----------------------------------------------------------------------

	template<> PalmEngineRoot* PalmEngineSingleton<PalmEngineRoot>::msSingleton = 0;
	PalmEngineRoot* PalmEngineRoot::GetSingletonPtr(void)
	{
		return msSingleton;
	}
	PalmEngineRoot& PalmEngineRoot::GetSingleton(void)
	{
		return (*msSingleton);
	}

	//-----------------------------------------------------------------------

	PalmEngineRoot::PalmEngineRoot() {}

	PalmEngineRoot::PalmEngineRoot(PalmEngineConfig& palmEngineConfig)
	{
		mConfig.reset(&palmEngineConfig);

		mLogManager.reset(new LogManager());
		mResourceManager.reset(new ResourceManager());
		mInputManager.reset(new InputManager());
		mRenderManager.reset(new RenderManager());
		mSceneManager.reset(new SceneManager());
		mWindowManager.reset(new WindowManager());

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
		mInputManager->StartUp();
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

			UpdateModules();
			RenderModules();
		}
	}

	void PalmEngineRoot::UpdateModules()
	{
		mInputManager->CollectInput(mWindowManager->GetMainWindow());
	}

	void PalmEngineRoot::RenderModules()
	{
		mRenderManager->Render(mWindowManager->GetMainWindow());
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