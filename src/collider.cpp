#include <palmx/collider.h>

#include "algo.h"
#include "solver.h"

namespace palmx::physics
{
    CollisionPoints SphereCollider::TestCollision(const Transform* transform, const Collider* collider, const Transform* collider_transform) const
    {
        return collider->TestCollision(collider_transform, this, transform);
    }

    CollisionPoints SphereCollider::TestCollision(const Transform* transform, const SphereCollider* sphere, const Transform* sphere_transform) const
    {
        return algo::FindSphereSphereCollisionPoints(this, transform, sphere, sphere_transform);
    }

    CollisionPoints SphereCollider::TestCollision(const Transform* transform, const PlaneCollider* plane, const Transform* plane_transform) const
    {
        return algo::FindSpherePlaneCollisionPoints(this, transform, plane, plane_transform);
    }

    CollisionPoints PlaneCollider::TestCollision(const Transform* transform, const Collider* collider, const Transform* collider_transform) const
    {
        return collider->TestCollision(collider_transform, this, transform);
    }

    CollisionPoints PlaneCollider::TestCollision(const Transform* transform, const SphereCollider* sphere, const Transform* sphere_transform) const
    {
        return algo::FindSpherePlaneCollisionPoints(sphere, sphere_transform, this, transform);
    }

    CollisionPoints PlaneCollider::TestCollision(const Transform* transform, const PlaneCollider* plane, const Transform* plane_transform) const
    {
        return CollisionPoints(); // No plane v plane
    }
}