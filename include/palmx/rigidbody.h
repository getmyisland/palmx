#ifndef PALMX_PHYSICS_RIGIDBODY_H
#define PALMX_PHYSICS_RIGIDBODY_H

#include <palmx/vector.h>

namespace palmx::physics
{
	struct Rigidbody
	{
		Vector3 velocity{ VECTOR_3_ZERO };
		Vector3 force{ VECTOR_3_ZERO };
		float mass{ 10 };
		bool is_dynamic{ true };
	};
}

#endif