#ifndef PALMX_RIGIDBODY_H_
#define PALMX_RIGIDBODY_H_

#include <glm/vec3.hpp>

namespace palmx
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