#ifndef PALMX_RENDERER_H
#define PALMX_RENDERER_H

#include <memory>

namespace palmx::render
{
	class Model;

	struct Renderer
	{
		std::unique_ptr<Model> mModel{ nullptr };
	};
}

#endif