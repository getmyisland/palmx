#ifndef PALMX_RENDERER_H
#define PALMX_RENDERER_H

#include <memory>

namespace palmx
{
	class Model;

	struct Renderer
	{
		std::unique_ptr<Model> mModel{ nullptr };
	};
}

#endif