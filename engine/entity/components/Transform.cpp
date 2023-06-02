#include "Transform.h"

#include <logging/LogManager.h>

#include <glm/detail/func_geometric.inl>
#include <glm/trigonometric.hpp>

namespace PalmEngine
{
	void Test(const int& i)
	{

	}

	Transform::Transform() //: _rotationChangeHook(mRotation, UpdateDirectionVectors)
	{
		UpdateDirectionVectors(mRotation);
	}

	void Transform::UpdateDirectionVectors(const glm::vec3& newValue)
	{
		PE_LOG_MANAGER->LogInfo("Updating Direction Vectors");

		// Calculate the new forward vector
		glm::vec3 forward;
		forward.x = cos(glm::radians(mRotation.y)) * cos(glm::radians(mRotation.x));
		forward.y = sin(glm::radians(mRotation.x));
		forward.z = sin(glm::radians(mRotation.y)) * cos(glm::radians(mRotation.x));
		mForward = glm::normalize(forward);
		// Also re-calculate the Right and Up vector
		mRight = glm::normalize(glm::cross(mForward, glm::vec3(0, 1, 0)));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement
		mUp = glm::normalize(glm::cross(mRight, mForward));
	}
}