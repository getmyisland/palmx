#ifndef PALMX_COLLIDER_H_
#define PALMX_COLLIDER_H_

#include "algo.h"
#include "../engine/Entity.h"
#include "../engine/Transform.h"

#include <glm/vec3.hpp>

#include <vector>

namespace palmx
{
    struct SphereCollider;
    struct PlaneCollider;

	struct CollisionPoints
	{
		glm::vec3 mA; // Furthest point of A into B
		glm::vec3 mB; // Furthest point of B into A
		glm::vec3 mNormal; // B - A normalized
		float mDepth; // Length of B - A
		bool mHasCollision = false;
	};

	struct Collision
	{
		EntityID* mEntityA;
		EntityID* mEntityB;
		CollisionPoints mPoints;
	};

	struct Collider
	{
		virtual CollisionPoints TestCollision(const Transform* transform, const Collider* collider, const Transform* colliderTransform) const = 0;

		virtual CollisionPoints TestCollision(const Transform* transform, const SphereCollider* sphere, const Transform* sphereTransform) const = 0;

		virtual CollisionPoints TestCollision(const Transform* transform, const PlaneCollider* plane, const Transform* planeTransform) const = 0;
	};

    struct SphereCollider : Collider
    {
        glm::vec3 mCenter;
        float mRadius;

        virtual CollisionPoints TestCollision(const Transform* transform, const Collider* collider, const Transform* colliderTransform) const override
        {
            return collider->TestCollision(colliderTransform, this, transform);
        }

        virtual CollisionPoints TestCollision(const Transform* transform, const SphereCollider* sphere, const Transform* sphereTransform) const override
        {
            return palmx::physics::algo::FindSphereSphereCollisionPoints(this, transform, sphere, sphereTransform);
        }

        virtual CollisionPoints TestCollision(const Transform* transform, const PlaneCollider* plane, const Transform* planeTransform) const override
        {
            return palmx::physics::algo::FindSpherePlaneCollisionPoints(this, transform, plane, planeTransform);
        }
    };

    struct PlaneCollider : Collider
    {
        glm::vec3 mPlane;
        float mDistance;

        virtual CollisionPoints TestCollision(const Transform* transform, const Collider* collider, const Transform* colliderTransform) const override
        {
            return collider->TestCollision(colliderTransform, this, transform);
        }

        virtual CollisionPoints TestCollision(const Transform* transform, const SphereCollider* sphere, const Transform* sphereTransform) const override
        {
            return palmx::physics::algo::FindSpherePlaneCollisionPoints(sphere, sphereTransform, this, transform);
        }

        virtual CollisionPoints TestCollision(const Transform* transform, const PlaneCollider* plane, const Transform* planeTransform) const override
        {
            return CollisionPoints(); // No plane v plane
        }
    };

	class Solver
	{
	public:
		virtual void Solve(std::vector<Collision>& collisions, float deltaTime) = 0;
	};
}

#endif