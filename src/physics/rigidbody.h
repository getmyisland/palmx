#ifndef PALMX_PHYSICS_RIGIDBODY_H
#define PALMX_PHYSICS_RIGIDBODY_H

#include <glm/vec3.hpp>

namespace palmx::physics
{
	class Rigidbody
	{
	public:
		glm::vec3 mVelocity = glm::vec3();
		glm::vec3 mForce = glm::vec3();
		float mMass = 10;
		bool mIsDynamic = true;
	};
}

#endif