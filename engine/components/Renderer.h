#ifndef _PE_RENDERER_H__
#define _PE_RENDERER_H__

#include <rendering/Model.h>
#include <rendering/Shader.h>
#include <components/Camera.h>
#include <components/Transform.h>

namespace PalmEngine
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void Render(Camera* camera, Transform* transform);

		void SetModel(Model& model);
		void SetShader(Shader& shader);

	private:
		Model* _model;
		Shader* _shader;
	};
}

#endif