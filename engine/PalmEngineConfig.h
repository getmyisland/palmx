#ifndef _PALM_ENGINE_CONFIG_H__
#define _PALM_ENGINE_CONFIG_H__

#include <scene/Scene.h>
#include <memory>

namespace PalmEngine
{
	class PalmEngineConfig
	{
	public:
		PalmEngineConfig(Scene &startScene, const unsigned int width, const unsigned int height) : mWidth(width), mHeight(height)
		{
			mStartScene.reset(&startScene);
		}

		~PalmEngineConfig()
		{
			mStartScene.release();
		}

	private:
		PalmEngineConfig() {}

	public:
		std::unique_ptr<Scene> mStartScene;

		unsigned int const mWidth{ 1920 };
		unsigned int const mHeight{ 1080 };
	};
}

#endif