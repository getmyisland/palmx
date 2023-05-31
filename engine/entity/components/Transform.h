#ifndef _PE_TRANSFORM_H__
#define _PE_TRANSFORM_H__

#include <glm/vec3.hpp>

#include <vector>

namespace PalmEngine
{
	class Transform
	{
	public:
		glm::vec3 GetLocalPosition() const;
		void SetLocalPosition(glm::vec3 localPosition);

		glm::vec3 GetLocalRotation() const;
		void SetLocalRotation(glm::vec3 localRotation);

		glm::vec3 GetLocalScale() const;
		void SetLocalScale(glm::vec3 localScale);

	private:
		glm::vec3 _localPosition = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 _localRotation = glm::vec3(0.0f, 0.0f, 0.0f); // Pitch, Yaw, Roll
		glm::vec3 _localScale = glm::vec3(1.0f, 1.0f, 1.0f);

		glm::vec3 _forward;
		glm::vec3 _right;
		glm::vec3 _up;

		void UpdateLocalDirectionVectors();
	};
}

#endif