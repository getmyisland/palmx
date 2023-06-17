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
		mpLogManager = std::make_unique<LogManager>();
		mpLogManager->StartUp();

		mpResourceManager = std::make_unique<ResourceManager>();
		mpResourceManager->StartUp();

		mpWindowManager = std::make_unique<WindowManager>();
		mpWindowManager->StartUp(config.mWidth, config.mHeight);

		mpInputManager = std::make_unique<InputManager>();
		mpInputManager->StartUp(mpWindowManager->GetMainWindow());

		mpRenderManager = std::make_unique<RenderManager>();
		mpRenderManager->StartUp();

		mpSceneManager = std::make_unique<SceneManager>();
		mpSceneManager->StartUp();
	}

	palmx::Root::~Root()
	{
		mpSceneManager.release();
		mpRenderManager.release();
		mpInputManager.release();
		mpWindowManager.release();
		mpResourceManager.release();
		mpLogManager.release();
	}

	void Root::Run(Scene& entryScene)
	{
		mpSceneManager->SetActiveScene(entryScene);

		GameLoop();

		mpSceneManager->ShutDown();
		mpRenderManager->ShutDown();
		mpInputManager->ShutDown();
		mpWindowManager->ShutDown();
		mpResourceManager->ShutDown();
		mpLogManager->ShutDown();
	}

	void Root::GameLoop()
	{
		float deltaTime = 0.0f;	// time between current frame and last frame
		float lastFrame = 0.0f;

		while (!glfwWindowShouldClose(mpWindowManager->GetMainWindow()))
		{
			float currentFrame = static_cast<float>(glfwGetTime());
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			mpInputManager->CollectInput(mpWindowManager->GetMainWindow());
			mpSceneManager->Update(deltaTime);

			mpRenderManager->Render(mpWindowManager->GetMainWindow(), mpSceneManager->GetActiveScene());
		}
	}

	void Root::Kill()
	{
		glfwSetWindowShouldClose(mpWindowManager->GetMainWindow(), true);
	}
}