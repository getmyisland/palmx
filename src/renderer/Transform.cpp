#include "Transform.h"

#include <glm/detail/func_geometric.inl>
#include <glm/trigonometric.hpp>

namespace palmx
{
	Transform::Transform()
	{
		UpdateDirectionVectors();
	}

	Transform::~Transform()
	{

	}

	glm::vec3 Transform::GetPosition() const
	{
		return _position;
	}

	void Transform::SetPosition(glm::vec3 position)
	{
		_position = position;
	}

	glm::vec3 Transform::GetRotation() const
	{
		return _rotation;
	}

	void Transform::SetRotation(glm::vec3 rotation)
	{
		_rotation = rotation;
		UpdateDirectionVectors();
	}

	glm::vec3 Transform::GetScale() const
	{
		return _scale;
	}

	void Transform::SetScale(glm::vec3 scale)
	{
		_scale = scale;
	}

	glm::vec3 Transform::GetForward() const
	{
		return _forward;
	}

	glm::vec3 Transform::GetRight() const
	{
		return _right;
	}

	glm::vec3 Transform::GetUp() const
	{
		return _up;
	}

	void Transform::UpdateDirectionVectors()
	{
		// Calculate the new forward vector
		glm::vec3 forward;
		forward.x = cos(glm::radians(_rotation.y)) * cos(glm::radians(_rotation.x));
		forward.y = sin(glm::radians(_rotation.x));
		forward.z = sin(glm::radians(_rotation.y)) * cos(glm::radians(_rotation.x));
		_forward = glm::normalize(forward);
		// Re-calculate the Right and Up vector
		_right = glm::normalize(glm::cross(_forward, glm::vec3(0, 1, 0)));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement
		_up = glm::normalize(glm::cross(_right, _forward));
	}
}