#include "physics_system.h"

#include "collider.h"
#include "rigidbody.h"
#include "../engine/scene.h"
#include "../engine/scene_view.h"
#include "../engine/transform.h"

#include <glm/vec3.hpp>

namespace palmx::physics
{
	const glm::vec3 gravity{ glm::vec3(0, -9.81, 0) };

	void PhysicsSystem::Step(float deltaTime, Scene* scene)
	{
		//ResolveCollisions(deltaTime, scene);

		for (EntityID entity : SceneView<Transform, Rigidbody>(*scene))
		{
			Rigidbody* rigidbody = scene->GetComponent<Rigidbody>(entity);
			Transform* transform = scene->GetComponent<Transform>(entity);

			// Apply gravity
			if (rigidbody->mIsDynamic)
			{
				rigidbody->mForce += rigidbody->mMass * gravity;

				rigidbody->mVelocity += (rigidbody->mForce / rigidbody->mMass) * deltaTime;
				transform->SetPosition(transform->GetPosition() + (rigidbody->mVelocity * deltaTime));

				rigidbody->mForce = glm::vec3();
			}
		}
	}

	void PhysicsSystem::ResolveCollisions(float deltaTime, Scene* scene)
	{
		for (EntityID entityA : SceneView<Transform, Collider>(*scene))
		{
			Transform* transformA = scene->GetComponent<Transform>(entityA);
			Collider* colliderA = scene->GetComponent<Collider>(entityA);

			for (EntityID entityB : SceneView<Transform, Collider>(*scene))
			{
				if (entityA == entityB)
				{
					break;
				}

				Transform* transformB = scene->GetComponent<Transform>(entityB);
				Collider* colliderB = scene->GetComponent<Collider>(entityB);

				CollisionPoints points = colliderA->TestCollision(transformA, colliderB, transformB);

				if (points.mHasCollision)
				{

				}
			}
		}
	}
}