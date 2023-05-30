#ifndef _PE_RENDERER_H__
#define _PE_RENDERER_H__

#include "Model.h"
#include "Shader.h"
#include <entity/Transform.h>

namespace PalmEngine
{
	class Renderer
	{
	public:
		Renderer(const Model& model, const Shader& shader);
		~Renderer();

		void Render(const Transform& transform);

	private:
		Renderer();

		const Model _model;
		const Shader _shader;
	};
}

#endif