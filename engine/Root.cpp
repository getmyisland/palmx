#include "Root.h"

namespace palmx
{
	template<> Root* Singleton<Root>::msSingleton = 0;
	Root* Root::GetSingletonPtr(void)
	{
		return msSingleton;
	}
	Root& Root::GetSingleton(void)
	{
		return (*msSingleton);
	}

	Root::Root() {}

	Root::Root(Config& config)
	{
		mConfig = std::make_unique<Config>(config);

		mLogManager = std::make_unique<LogManager>();
		mResourceManager = std::make_unique<ResourceManager>();
		mInputManager = std::make_unique<InputManager>();
		mRenderManager = std::make_unique<RenderManager>();
		mSceneManager = std::make_unique<SceneManager>();
		mWindowManager = std::make_unique<WindowManager>();

		StartModules();
	}

	palmx::Root::~Root() 
	{
		mSceneManager.release();
		mRenderManager.release();
		mInputManager.release();
		mResourceManager.release();
		mLogManager.release();
		mWindowManager.release();

		mConfig.release();
	}

	void Root::StartModules()
	{
		mWindowManager->StartUp();
		mLogManager->StartUp();
		mResourceManager->StartUp();
		mInputManager->StartUp(mWindowManager->GetMainWindow());
		mRenderManager->StartUp();
		mSceneManager->StartUp();
	}

	void Root::Run(Scene& entryScene)
	{
		mSceneManager->SetActiveScene(entryScene);

		GameLoop();
		ShutdownModules();
	}

	void Root::GameLoop()
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

	void Root::ShutdownModules()
	{
		mSceneManager->ShutDown();
		mRenderManager->ShutDown();
		mInputManager->ShutDown();
		mResourceManager->ShutDown();
		mLogManager->ShutDown();
		mWindowManager->ShutDown();
	}

	void Root::Kill()
	{
		glfwSetWindowShouldClose(mWindowManager->GetMainWindow(), true);
	}
}