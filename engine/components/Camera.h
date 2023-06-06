#ifndef _PE_CAMERA_H__
#define _PE_CAMERA_H__

#include <components/Transform.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

namespace PalmEngine
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		glm::mat4 GetViewMatrix();

		float GetZoom() const;
		void SetZoom(float zoom);

		void SetTransform(Transform& transform);

	private:
		float _zoom{ 45 };

		Transform* _transform;
	};
}

#endif