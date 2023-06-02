#include "Camera.h"

namespace PalmEngine
{
	Camera::Camera() {}

	Camera::Camera(Transform& transform) : _transform(&transform)
	{

	}

	glm::mat4 Camera::GetViewMatrix()
	{
		return glm::lookAt(_transform->mPosition, _transform->mPosition + _transform->mForward, _transform->mUp);
	}

	float Camera::GetZoom() const
	{
		return _zoom;
	}

	void Camera::SetZoom(float zoom)
	{
		_zoom = zoom;
	}
}