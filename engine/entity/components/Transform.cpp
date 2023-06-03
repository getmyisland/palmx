#include "Transform.h"

#include <logging/LogManager.h>

#include <glm/detail/func_geometric.inl>
#include <glm/trigonometric.hpp>

namespace PalmEngine
{
	Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : _position(position), _rotation(rotation), _scale(scale)
	{
		UpdateDirectionVectors();
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

	void Transform::SetForward(glm::vec3 forward)
	{
		_forward = forward;
	}

	glm::vec3 Transform::GetRight() const
	{
		return _right;
	}

	void Transform::SetRight(glm::vec3 right)
	{
		_right = right;
	}

	glm::vec3 Transform::GetUp() const
	{
		return _up;
	}

	void Transform::SetUp(glm::vec3 up)
	{
		_up = up;
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