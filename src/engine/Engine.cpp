#include "Engine.h"

#include "ResourceManager.h"

namespace palmx
{
	template<> Engine* Singleton<Engine>::msSingleton = 0;
	Engine* Engine::GetSingletonPtr(void)
	{
		return msSingleton;
	}
	Engine& Engine::GetSingleton(void)
	{
		return (*msSingleton);
	}

	Engine::Engine() {}

	Engine::Engine(Config& config)
	{
		mGuiSystem = std::make_unique<GuiSystem>();
		mGuiSystem->Start(config.mWidth, config.mHeight);

		mInputSystem = std::make_unique<InputSystem>();
		mInputSystem->Start(mGuiSystem->GetMainWindow());

		mRenderSystem = std::make_unique<RenderSystem>();
		mRenderSystem->Start();

		mSceneManager = std::make_unique<SceneManager>();
	}

	palmx::Engine::~Engine()
	{
		mSceneManager.release();
		mPhysicsSystem.release();
		mRenderSystem.release();
		mInputSystem.release();
		mGuiSystem.release();
	}

	void Engine::Run(Scene& entryScene)
	{
		mSceneManager->SetActiveScene(entryScene);

		GameLoop();

		mRenderSystem->Stop();
		mInputSystem->Stop();
		mGuiSystem->Stop();
	}

	void Engine::GameLoop()
	{
		float deltaTime = 0.0f;	// time between current frame and last frame
		float lastFrame = 0.0f;

		const float PHYSICS_TIMESTEP = 0.5;
		float fixedDeltaTime = 0.0f;

		while (!glfwWindowShouldClose(mGuiSystem->GetMainWindow()))
		{
			float currentFrame = static_cast<float>(glfwGetTime());
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			fixedDeltaTime += deltaTime;
			if (fixedDeltaTime >= PHYSICS_TIMESTEP)
			{
				fixedDeltaTime = 0;
				mPhysicsSystem->Step(deltaTime, mSceneManager->GetActiveScene());
			}

			// First collect the input
			mInputSystem->CollectInput(mGuiSystem->GetMainWindow());

			// Then update all entities in the scene
			mSceneManager->Update(deltaTime);

			// Now render the scene
			mRenderSystem->Render(mGuiSystem->GetMainWindow(), mSceneManager->GetActiveScene());
		}
	}

	void Engine::Kill()
	{
		glfwSetWindowShouldClose(mGuiSystem->GetMainWindow(), true);
	}
}