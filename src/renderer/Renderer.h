#ifndef PALMX_RENDERER_H_
#define PALMX_RENDERER_H_

#include <memory>

namespace palmx
{
	class Model;
	class Shader;
	class Transform;

	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void Render(const std::shared_ptr<Shader> shader, const Transform& transform);

		std::unique_ptr<Model> mModel{ nullptr };
	};
}

#endif