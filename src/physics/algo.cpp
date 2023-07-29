#include "algo.h"

#include "collider.h"
#include "../engine/transform.h"

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

namespace palmx::physics::algo
{
	CollisionPoints FindSphereSphereCollisionPoints(const SphereCollider* a, const Transform* ta, const SphereCollider* b, const Transform* tb)
	{
		glm::vec3 center_a = ta->GetPosition() + a->center;
		glm::vec3 center_b = tb->GetPosition() + b->center;

		glm::vec3 distance_vec = center_b - center_a;
		float distance = glm::length(distance_vec);

		float sum_radius = a->radius + b->radius;

		if (distance <= sum_radius)
		{
			glm::vec3 collision_normal = glm::normalize(distance_vec);
			float collision_depth = sum_radius - distance;

			return { center_a - collision_normal * a->radius, center_b - collision_normal * b->radius, collision_normal, collision_depth, true };
		}

		return {};
	}

	CollisionPoints FindSpherePlaneCollisionPoints(const SphereCollider* a, const Transform* ta, const PlaneCollider* b, const Transform* tb)
	{
		glm::vec3 center_a = ta->GetPosition() + a->center;

		float distance = glm::dot(center_a, b->plane) - b->distance;

		if (distance <= a->radius)
		{
			glm::vec3 collision_normal = glm::normalize(b->plane);
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
		glm::vec3 temp_a = points.a;
		points.a = points.b;
		points.b = temp_a;

		points.normal = -points.normal;

		return points;
	}
}