#include "Camera.h"

#include <debug/LogManager.h>

namespace palmx
{
	Camera::Camera() 
	{

	}

	Camera::~Camera()
	{

	}

	glm::mat4 Camera::GetViewMatrix(const Transform& transform) const
	{
		return glm::lookAt(transform.GetPosition(), transform.GetPosition() + transform.GetForward(), transform.GetUp());
	}
}