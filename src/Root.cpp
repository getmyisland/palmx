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
		mLogManager = std::make_unique<LogManager>();
		mLogManager->StartUp();

		mResourceManager = std::make_unique<ResourceManager>();
		mResourceManager->StartUp();

		mWindowManager = std::make_unique<WindowManager>();
		mWindowManager->StartUp(config.mWidth, config.mHeight);

		mInputManager = std::make_unique<InputManager>();
		mInputManager->StartUp(mWindowManager->GetMainWindow());

		mRenderManager = std::make_unique<RenderManager>();
		mRenderManager->StartUp();

		mSceneManager = std::make_unique<SceneManager>();
		mSceneManager->StartUp();
	}

	palmx::Root::~Root()
	{
		mSceneManager.release();
		mRenderManager.release();
		mInputManager.release();
		mWindowManager.release();
		mResourceManager.release();
		mLogManager.release();
	}

	void Root::Run(Scene& entryScene)
	{
		mSceneManager->SetActiveScene(entryScene);

		GameLoop();

		mSceneManager->ShutDown();
		mRenderManager->ShutDown();
		mInputManager->ShutDown();
		mWindowManager->ShutDown();
		mResourceManager->ShutDown();
		mLogManager->ShutDown();
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

	void Root::Kill()
	{
		glfwSetWindowShouldClose(mWindowManager->GetMainWindow(), true);
	}
}