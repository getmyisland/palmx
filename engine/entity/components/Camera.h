#ifndef _PE_CAMERA_H__
#define _PE_CAMERA_H__

#include <entity/components/Transform.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

namespace PalmEngine
{
	class Camera
	{
	public:
		Camera(Transform& transform);

		glm::mat4 GetViewMatrix();
	
		float GetZoom() const;
		void SetZoom(float zoom);

	private:
		Camera();

		Transform* _transform;

		float _zoom = 45;
	};
}

#endif