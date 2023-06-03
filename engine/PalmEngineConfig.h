#ifndef _PALM_ENGINE_CONFIG_H__
#define _PALM_ENGINE_CONFIG_H__

namespace PalmEngine
{
	class PalmEngineConfig
	{
	public:
		PalmEngineConfig(const unsigned int width = 800, const unsigned int height = 600) : _width(width), _height(height) {}
		~PalmEngineConfig() {}

		const unsigned int GetWidth() const
		{
			return _width;
		}

		void SetWidth(const unsigned int width)
		{
			_width = width;
		}

		const unsigned int GetHeight() const
		{
			return _height;
		}

		void SetHeight(const unsigned int height)
		{
			_height = height;
		}

	private:
		unsigned int _width;
		unsigned int _height;
	};
}

#endif