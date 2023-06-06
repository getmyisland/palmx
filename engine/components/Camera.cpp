#include "Camera.h"

#include <logging/LogManager.h>

namespace PalmEngine
{
	Camera::Camera() 
	{

	}

	Camera::~Camera()
	{

	}

	glm::mat4 Camera::GetViewMatrix()
	{
		return glm::lookAt(_transform->GetPosition(), _transform->GetPosition() + _transform->GetForward(), _transform->GetUp());
	}

	float Camera::GetZoom() const
	{
		return _zoom;
	}

	void Camera::SetZoom(float zoom)
	{
		_zoom = zoom;
	}

	void Camera::SetTransform(Transform& transform)
	{
		_transform = &transform;
	}
}