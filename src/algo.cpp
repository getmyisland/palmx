#include "algo.h"

#include "solver.h"

#include <palmx/collider.h>
#include <palmx/transform.h>
#include <palmx/vector.h>

namespace palmx::physics::algo
{
	CollisionPoints FindSphereSphereCollisionPoints(const SphereCollider* a, const Transform* ta, const SphereCollider* b, const Transform* tb)
	{
		Vector3 center_a = ta->position + a->center;
		Vector3 center_b = tb->position + b->center;

		Vector3 distance_vec = center_b - center_a;
		float distance = distance_vec.Length();

		float sum_radius = a->radius + b->radius;

		if (distance <= sum_radius)
		{
			Vector3 collision_normal = distance_vec.Normalize();
			float collision_depth = sum_radius - distance;

			return { center_a - collision_normal * a->radius, center_b - collision_normal * b->radius, collision_normal, collision_depth, true };
		}

		return {};
	}

	CollisionPoints FindSpherePlaneCollisionPoints(const SphereCollider* a, const Transform* ta, const PlaneCollider* b, const Transform* tb)
	{
		Vector3 center_a = ta->position + a->center;

		float distance = center_a.Dot(b->plane) - b->distance;

		if (distance <= a->radius)
		{
			Vector3 collision_normal = b->plane.Normalize();
			float collision_depth = a->radius - distance;

			return { center_a - collision_normal * a->radius, center_a - collision_normal * (a->radius - collision_depth), collision_normal, collision_depth, true };
		}

		return {};
	}

	CollisionPoints FindPlaneSphereCollisionPoints(const PlaneCollider* a, const Transform* ta, const SphereCollider* b, const Transform* tb)
	{
		// Reuse the sphere code
		CollisionPoints points = b->TestCollision(tb, a, ta);

		// Swap the points and normal
		Vector3 temp_a = points.a;
		points.a = points.b;
		points.b = temp_a;

		points.normal = -points.normal;

		return points;
	}
}