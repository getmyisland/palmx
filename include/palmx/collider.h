#ifndef PALMX_PHYSICS_COLLIDER_H
#define PALMX_PHYSICS_COLLIDER_H

#include <palmx/vector.h>

namespace palmx
{
    struct Transform;

    namespace physics
    {
        struct CollisionPoints;
        struct SphereCollider;
        struct PlaneCollider;

        struct Collider
        {
            virtual CollisionPoints TestCollision(const Transform* transform, const Collider* collider, const Transform* collider_transform) const = 0;
            virtual CollisionPoints TestCollision(const Transform* transform, const SphereCollider* sphere, const Transform* sphere_transform) const = 0;
            virtual CollisionPoints TestCollision(const Transform* transform, const PlaneCollider* plane, const Transform* plane_transform) const = 0;
        };

        struct SphereCollider : Collider
        {
            Vector3 center{ VECTOR_3_ZERO };
            float radius{ 0.5f };

            virtual CollisionPoints TestCollision(const Transform* transform, const Collider* collider, const Transform* collider_transform) const override;
            virtual CollisionPoints TestCollision(const Transform* transform, const SphereCollider* sphere, const Transform* sphere_transform) const override;
            virtual CollisionPoints TestCollision(const Transform* transform, const PlaneCollider* plane, const Transform* plane_transform) const override;
        };

        // TODO Box Collider instead of Plane Collider
        struct PlaneCollider : Collider
        {
            Vector3 plane;
            float distance;

            virtual CollisionPoints TestCollision(const Transform* transform, const Collider* collider, const Transform* collider_transform) const override;
            virtual CollisionPoints TestCollision(const Transform* transform, const SphereCollider* sphere, const Transform* sphere_transform) const override;
            virtual CollisionPoints TestCollision(const Transform* transform, const PlaneCollider* plane, const Transform* plane_transform) const override;
        };
    }
}

#endif