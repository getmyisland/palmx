#ifndef PALMX_PHYSICS_ALGO_H
#define PALMX_PHYSICS_ALGO_H

namespace palmx
{
	struct Transform;

	namespace physics
	{
		struct Collider;
		struct CollisionPoints;
		struct SphereCollider;
		struct PlaneCollider;

		namespace algo
		{
			CollisionPoints FindSphereSphereCollisionPoints(const SphereCollider* a, const Transform* ta, const SphereCollider* b, const Transform* tb);
			CollisionPoints FindSpherePlaneCollisionPoints(const SphereCollider* a, const Transform* ta, const PlaneCollider* b, const Transform* tb);
			CollisionPoints FindPlaneSphereCollisionPoints(const PlaneCollider* a, const Transform* ta, const SphereCollider* b, const Transform* tb);
		}
	}
}

#endif