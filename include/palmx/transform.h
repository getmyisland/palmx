#ifndef PALMX_TRANSFORM_H
#define PALMX_TRANSFORM_H

#include <palmx/vector.h>

namespace palmx
{
	struct Transform
	{
		Vector3 position{ VECTOR_3_ZERO };
		Vector3 rotation{ VECTOR_3_ZERO }; // Pitch, Yaw, Roll
		Vector3 scale{ VECTOR_3_ONE };
	};
}

#endif