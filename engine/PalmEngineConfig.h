#ifndef _PALM_ENGINE_CONFIG_H__
#define _PALM_ENGINE_CONFIG_H__

namespace PalmEngine
{
	class PalmEngineConfig
	{
	public:
		PalmEngineConfig(const unsigned int width, const unsigned int height) : mWidth(width), mHeight(height) {}
		~PalmEngineConfig() {}

	private:
		PalmEngineConfig() {}

	public:
		unsigned int const mWidth{ 1920 };
		unsigned int const mHeight{ 1080 };
	};
}

#endif