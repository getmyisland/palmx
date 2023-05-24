#ifndef _PALM_ENGINE_CONFIG_H__
#define _PALM_ENGINE_CONFIG_H__

namespace PalmEngine
{
	class PalmEngineConfig
	{
	public:
		PalmEngineConfig(const unsigned int width, const unsigned int height) : _width(width), _height(height) {}
		~PalmEngineConfig() {}

	private:
		PalmEngineConfig() {}

	public:
		const unsigned int GetWidth() const
		{
			return _width;
		}

		const unsigned int GetHeigth() const
		{
			return _height;
		}

	private:
		const unsigned int _width { 1920 };
		const unsigned int _height { 1080 };
	};
}

#endif