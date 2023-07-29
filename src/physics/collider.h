#ifndef PALMX_PHYSICS_COLLIDER_H
#define PALMX_PHYSICS_COLLIDER_H

#include "algo.h"
#include "../engine/entity.h"
#include "../engine/transform.h"

#include <glm/vec3.hpp>

#include <vector>

namespace palmx::physics
{
    struct SphereCollider;
    struct PlaneCollider;

	struct CollisionPoints
	{
		glm::vec3 a = glm::vec3(); // Furthest point of A into B
		glm::vec3 b = glm::vec3(); // Furthest point of B into A
		glm::vec3 normal = glm::vec3(); // B - A normalized
		float depth = 0; // Length of B - A
		bool has_collided = false;
	};

	struct Collision
	{
		EntityID* entity_a;
		EntityID* entity_b;
		CollisionPoints points;
	};

	struct Collider
	{
		virtual CollisionPoints TestCollision(const Transform* transform, const Collider* collider, const Transform* collider_transform) const = 0;

		virtual CollisionPoints TestCollision(const Transform* transform, const SphereCollider* sphere, const Transform* sphere_transform) const = 0;

		virtual CollisionPoints TestCollision(const Transform* transform, const PlaneCollider* plane, const Transform* plane_transform) const = 0;
	};

    struct SphereCollider : Collider
    {
        glm::vec3 center;
        float radius;

        virtual CollisionPoints TestCollision(const Transform* transform, const Collider* collider, const Transform* collider_transform) const override
        {
            return collider->TestCollision(collider_transform, this, transform);
        }

        virtual CollisionPoints TestCollision(const Transform* transform, const SphereCollider* sphere, const Transform* sphere_transform) const override
        {
            return algo::FindSphereSphereCollisionPoints(this, transform, sphere, sphere_transform);
        }

        virtual CollisionPoints TestCollision(const Transform* transform, const PlaneCollider* plane, const Transform* plane_transform) const override
        {
            return algo::FindSpherePlaneCollisionPoints(this, transform, plane, plane_transform);
        }
    };

    struct PlaneCollider : Collider
    {
        glm::vec3 plane;
        float distance;

        virtual CollisionPoints TestCollision(const Transform* transform, const Collider* collider, const Transform* collider_transform) const override
        {
            return collider->TestCollision(collider_transform, this, transform);
        }

        virtual CollisionPoints TestCollision(const Transform* transform, const SphereCollider* sphere, const Transform* sphere_transform) const override
        {
            return algo::FindSpherePlaneCollisionPoints(sphere, sphere_transform, this, transform);
        }

        virtual CollisionPoints TestCollision(const Transform* transform, const PlaneCollider* plane, const Transform* plane_transform) const override
        {
            return CollisionPoints(); // No plane v plane
        }
    };

	class Solver
	{
	public:
		virtual void Solve(std::vector<Collision>& collisions, float delta_time) = 0;
	};
}

#endif