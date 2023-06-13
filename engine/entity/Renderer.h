#ifndef PALMX_RENDERER_H_
#define PALMX_RENDERER_H_

#include <rendering/Model.h>
#include <rendering/Shader.h>
#include <scene/components/Camera.h>
#include <scene/components/Transform.h>

namespace palmx
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void Render(const MainCamera& mainCamera, const Transform& transform);

		void SetModel(Model& model);
		void SetShader(Shader& shader);

	private:
		Model* _model{ nullptr };
		Shader* _shader{ nullptr };
	};
}

#endif