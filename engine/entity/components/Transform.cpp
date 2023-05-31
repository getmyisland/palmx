#include "Transform.h"

#include <glm/detail/func_geometric.inl>
#include <glm/trigonometric.hpp>

namespace PalmEngine
{
	glm::vec3 Transform::GetLocalPosition() const
	{
		return _localPosition;
	}

	void Transform::SetLocalPosition(glm::vec3 localPosition)
	{
		_localPosition = localPosition;
	}

	glm::vec3 Transform::GetLocalRotation() const
	{
		return _localRotation;
	}

	void Transform::SetLocalRotation(glm::vec3 localRotation)
	{
		_localRotation = localRotation;
	}

	glm::vec3 Transform::GetLocalScale() const
	{
		return _localScale;
	}

	void Transform::SetLocalScale(glm::vec3 localScale)
	{
		_localScale = localScale;
	}

	void Transform::UpdateLocalDirectionVectors()
	{
		// calculate the new Front vector
		glm::vec3 forward;
		forward.x = cos(glm::radians(_localRotation.y)) * cos(glm::radians(_localRotation.x));
		forward.y = sin(glm::radians(_localRotation.x));
		forward.z = sin(glm::radians(_localRotation.y)) * cos(glm::radians(_localRotation.x));
		_forward = glm::normalize(forward);
		// also re-calculate the Right and Up vector
		_right = glm::normalize(glm::cross(_forward, glm::vec3(0, 1, 0)));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		_up = glm::normalize(glm::cross(_right, _forward));
	}
}