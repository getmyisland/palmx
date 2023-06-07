#ifndef _PE_CAMERA_H__
#define _PE_CAMERA_H__

#include <scene/components/Transform.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

namespace PalmEngine
{
	class Camera;

	struct MainCamera
	{
		MainCamera(const Camera& camera, const Transform& transform) : m_Camera(&camera), m_Transform(&transform) {}
		~MainCamera() {}

		const Camera* m_Camera;
		const Transform* m_Transform;
	};

	class Camera
	{
	public:
		Camera();
		~Camera();

		glm::mat4 GetViewMatrix(const Transform& transform) const;

		float m_Zoom{ 45 };
	};
}

#endif