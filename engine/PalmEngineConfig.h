#ifndef _PALM_ENGINE_CONFIG_H__
#define _PALM_ENGINE_CONFIG_H__

#include <PalmEngineEntry.h>
#include <memory>

namespace PalmEngine
{
	class PalmEngineConfig
	{
	public:
		PalmEngineConfig(PalmEngineEntry &palmEngineEntry, const unsigned int width, const unsigned int height) : mWidth(width), mHeight(height)
		{
			mPalmEngineEntry.reset(&palmEngineEntry);
		}

		~PalmEngineConfig()
		{
			mPalmEngineEntry.release();
		}

		std::unique_ptr<PalmEngineEntry> mPalmEngineEntry;

		unsigned int const mWidth{ 1920 };
		unsigned int const mHeight{ 1080 };

	private:
		PalmEngineConfig() {}
	};
}

#endif