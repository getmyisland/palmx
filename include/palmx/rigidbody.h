#ifndef PALMX_PHYSICS_RIGIDBODY_H
#define PALMX_PHYSICS_RIGIDBODY_H

#include <glm/vec3.hpp>

namespace palmx::physics
{
	struct Rigidbody
	{
		glm::vec3 velocity = glm::vec3();
		glm::vec3 force = glm::vec3();
		float mass = 10;
		bool is_dynamic = true;
	};
}

#endif