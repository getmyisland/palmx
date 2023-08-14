#include <palmx/transform.h>

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
		return position_;
	}

	void Transform::SetPosition(glm::vec3 position)
	{
		position_ = position;
	}

	glm::vec3 Transform::GetRotation() const
	{
		return rotation_;
	}

	void Transform::SetRotation(glm::vec3 rotation)
	{
		rotation_ = rotation;
		UpdateDirectionVectors();
	}

	glm::vec3 Transform::GetScale() const
	{
		return scale_;
	}

	void Transform::SetScale(glm::vec3 scale)
	{
		scale_ = scale;
	}

	glm::vec3 Transform::GetForward() const
	{
		return forward_;
	}

	glm::vec3 Transform::GetRight() const
	{
		return right_;
	}

	glm::vec3 Transform::GetUp() const
	{
		return up_;
	}

	void Transform::UpdateDirectionVectors()
	{
		// Calculate the new forward vector
		glm::vec3 forward;
		forward.x = cos(glm::radians(rotation_.y)) * cos(glm::radians(rotation_.x));
		forward.y = sin(glm::radians(rotation_.x));
		forward.z = sin(glm::radians(rotation_.y)) * cos(glm::radians(rotation_.x));
		forward_ = glm::normalize(forward);
		// Re-calculate the Right and Up vector
		right_ = glm::normalize(glm::cross(forward_, glm::vec3(0, 1, 0)));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement
		up_ = glm::normalize(glm::cross(right_, forward_));
	}
}