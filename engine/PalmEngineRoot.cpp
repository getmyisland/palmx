#include "PalmEngineRoot.h"

namespace PalmEngine
{
	//-----------------------------------------------------------------------

	void framebuffer_size_callback(GLFWwindow* pWindow, int width, int height);

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
		// Initialize and configure glfw
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		// Create glfw window
		GLFWwindow* window = glfwCreateWindow(palmEngineConfig.mWidth, palmEngineConfig.mHeight, "Palm Engine", NULL, NULL);
		if (window == NULL)
		{
			PE_LOG_MANAGER->LogError("Failed to create GLFW window");
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		_window = window;

		mLogManager.reset(new LogManager());
		mResourceManager.reset(new ResourceManager());
		mInputManager.reset(new InputManager());
		mRenderManager.reset(new RenderManager());
		mSceneManager.reset(new SceneManager());

		StartUpModules();
		GameLoop();
		ShutdownModules();

		glfwTerminate();
	}

	PalmEngine::PalmEngineRoot::~PalmEngineRoot() 
	{
		mSceneManager.release();
		mRenderManager.release();
		mInputManager.release();
		mResourceManager.release();
		mLogManager.release();
	}

	void PalmEngineRoot::StartUpModules()
	{
		mLogManager->StartUp();
		mResourceManager->StartUp();
		mInputManager->StartUp();
		mRenderManager->StartUp();
		mSceneManager->StartUp();
	}

	void PalmEngineRoot::GameLoop()
	{
		float deltaTime = 0.0f;	// time between current frame and last frame
		float lastFrame = 0.0f;

		while (!glfwWindowShouldClose(_window))
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
		mInputManager->CollectInput(_window);
	}

	void PalmEngineRoot::RenderModules()
	{
		mRenderManager->Render(_window);
	}

	void PalmEngineRoot::ShutdownModules()
	{
		mSceneManager->ShutDown();
		mRenderManager->ShutDown();
		mInputManager->ShutDown();
		mResourceManager->ShutDown();
		mLogManager->ShutDown();
	}

	void PalmEngineRoot::KillGameLoop()
	{
		glfwSetWindowShouldClose(_window, true);
	}

	void framebuffer_size_callback(GLFWwindow* pWindow, int width, int height)
	{
		// make sure the viewport matches the new window dimensions; note that width and 
		// height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);
	}
}