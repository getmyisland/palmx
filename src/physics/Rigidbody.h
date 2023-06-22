#ifndef PALMX_RIGIDBODY_H_
#define PALMX_RIGIDBODY_H_

#include <glm/vec3.hpp>

namespace palmx
{
	class Rigidbody
	{
	public:
		glm::vec3 mVelocity;
		glm::vec3 mForce;
		float mMass;
	};
}

#endif