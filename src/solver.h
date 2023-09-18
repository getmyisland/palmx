#ifndef PALMX_PHYSICS_SOLVER_H
#define PALMX_PHYSICS_SOLVER_H

#include <palmx/entity.h>
#include <palmx/vector.h>

#include <vector>

namespace palmx::physics
{
    struct CollisionPoints
    {
        Vector3 a = Vector3(); // Furthest point of A into B
        Vector3 b = Vector3(); // Furthest point of B into A
        Vector3 normal = Vector3(); // B - A normalized
        float depth = 0; // Length of B - A
        bool has_collided = false;
    };

    struct Collision
    {
        EntityID* entity_a;
        EntityID* entity_b;
        CollisionPoints points;
    };

    class Solver
    {
    public:
        virtual void Solve(std::vector<Collision>& collisions, float delta_time) = 0;
    };
}

#endif