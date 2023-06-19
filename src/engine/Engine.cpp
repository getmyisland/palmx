#include "Engine.h"

#include "InputModule.h"
#include "SceneModule.h"
#include "../gui/GuiModule.h"
#include "../renderer/RenderModule.h"
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
		mWindowModule = std::make_unique<GuiModule>();
		mWindowModule->StartUp(config.mWidth, config.mHeight);

		mInputModule = std::make_unique<InputModule>();
		mInputModule->StartUp(mWindowModule->GetMainWindow());

		mRenderModule = std::make_unique<RenderModule>();
		mRenderModule->StartUp();

		mSceneModule = std::make_unique<SceneModule>();
		mSceneModule->StartUp();
	}

	palmx::Engine::~Engine()
	{
		mSceneModule.release();
		mRenderModule.release();
		mInputModule.release();
		mWindowModule.release();
	}

	void Engine::Run(Scene& entryScene)
	{
		mSceneModule->SetActiveScene(entryScene);

		GameLoop();

		mSceneModule->ShutDown();
		mRenderModule->ShutDown();
		mInputModule->ShutDown();
		mWindowModule->ShutDown();
	}

	void Engine::GameLoop()
	{
		float deltaTime = 0.0f;	// time between current frame and last frame
		float lastFrame = 0.0f;

		while (!glfwWindowShouldClose(mWindowModule->GetMainWindow()))
		{
			float currentFrame = static_cast<float>(glfwGetTime());
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			mInputModule->CollectInput(mWindowModule->GetMainWindow());
			mSceneModule->Update(deltaTime);

			mRenderModule->Render(mWindowModule->GetMainWindow(), mSceneModule->GetActiveScene());
		}
	}

	void Engine::Kill()
	{
		glfwSetWindowShouldClose(mWindowModule->GetMainWindow(), true);
	}
}