#ifndef PALMX_RENDERER_H_
#define PALMX_RENDERER_H_

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