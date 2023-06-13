#ifndef PALMX_CONFIG_H_
#define PALMX_CONFIG_H_

namespace palmx
{
	class Config
	{
	public:
		Config(const unsigned int width = 800, const unsigned int height = 600) : _width(width), _height(height) {}
		~Config() {}

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