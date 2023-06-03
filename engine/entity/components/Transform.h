#ifndef _PE_TRANSFORM_H__
#define _PE_TRANSFORM_H__

#include <glm/vec3.hpp>

namespace PalmEngine
{
	class Transform
	{
	public:
		Transform(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));

		glm::vec3 GetPosition() const;
		void SetPosition(glm::vec3 position);

		glm::vec3 GetRotation() const;
		void SetRotation(glm::vec3 rotation);

		glm::vec3 GetScale() const;
		void SetScale(glm::vec3 scale);

		glm::vec3 GetForward() const;
		void SetForward(glm::vec3 forward);
		glm::vec3 GetRight() const;
		void SetRight(glm::vec3 right);
		glm::vec3 GetUp() const;
		void SetUp(glm::vec3 up);

	private:
		glm::vec3 _position;
		glm::vec3 _rotation; // Pitch, Yaw, Roll
		glm::vec3 _scale;

		glm::vec3 _forward;
		glm::vec3 _right;
		glm::vec3 _up;

		void UpdateDirectionVectors();
	};
}

#endif