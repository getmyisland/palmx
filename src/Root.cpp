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
		mpConfig = std::make_unique<Config>(config);

		mpLogManager = std::make_unique<LogManager>();
		mpResourceManager = std::make_unique<ResourceManager>();
		mpInputManager = std::make_unique<InputManager>();
		mpRenderManager = std::make_unique<RenderManager>();
		mpSceneManager = std::make_unique<SceneManager>();
		mpWindowManager = std::make_unique<WindowManager>();

		StartModules();
	}

	palmx::Root::~Root() 
	{
		mpSceneManager.release();
		mpRenderManager.release();
		mpInputManager.release();
		mpResourceManager.release();
		mpLogManager.release();
		mpWindowManager.release();

		mpConfig.release();
	}

	void Root::StartModules()
	{
		mpWindowManager->StartUp(mpConfig->mWidth, mpConfig->mHeight);
		mpLogManager->StartUp();
		mpResourceManager->StartUp();
		mpInputManager->StartUp(mpWindowManager->GetMainWindow());
		mpRenderManager->StartUp();
		mpSceneManager->StartUp();
	}

	void Root::Run(Scene& entryScene)
	{
		mpSceneManager->SetActiveScene(entryScene);

		GameLoop();
		ShutdownModules();
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

	void Root::ShutdownModules()
	{
		mpSceneManager->ShutDown();
		mpRenderManager->ShutDown();
		mpInputManager->ShutDown();
		mpResourceManager->ShutDown();
		mpLogManager->ShutDown();
		mpWindowManager->ShutDown();
	}

	void Root::Kill()
	{
		glfwSetWindowShouldClose(mpWindowManager->GetMainWindow(), true);
	}
}