#ifndef PALMX_COLLIDER_H_
#define PALMX_COLLIDER_H_

#include <glm/vec3.hpp>

namespace palmx
{
	struct CollisionPoints
	{
		glm::vec3 mA; // Furthest point of A into B
		glm::vec3 mB; // Furthest point of B into A
		glm::vec3 mNormal; // B - A normalized
		float mDepth; // Length of B - A
	};
}

#endif