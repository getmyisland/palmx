#ifndef PALMX_TRANSFORM_H_
#define PALMX_TRANSFORM_H_

#include <glm/vec3.hpp>

namespace palmx
{
	struct Transform
	{
	public:
		Transform();
		~Transform();

		glm::vec3 GetPosition() const;
		void SetPosition(glm::vec3 position);

		glm::vec3 GetRotation() const;
		void SetRotation(glm::vec3 rotation);

		glm::vec3 GetScale() const;
		void SetScale(glm::vec3 scale);

		glm::vec3 GetForward() const;
		glm::vec3 GetRight() const;
		glm::vec3 GetUp() const;

	private:
		glm::vec3 _position{ glm::vec3(0.0f, 0.0f, 0.0f) };
		glm::vec3 _rotation{ glm::vec3(0.0f, 0.0f, 0.0f) }; // Pitch, Yaw, Roll
		glm::vec3 _scale{ glm::vec3(1.0f, 1.0f, 1.0f) };

		glm::vec3 _forward;
		glm::vec3 _right;
		glm::vec3 _up;

		void UpdateDirectionVectors();
	};
}

#endif