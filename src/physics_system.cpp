#include <palmx/physics_system.h>

#include <palmx/collider.h>
#include <palmx/rigidbody.h>
#include <palmx/scene.h>
#include <palmx/scene_view.h>
#include <palmx/transform.h>

#include <glm/vec3.hpp>

namespace palmx::physics
{
	const glm::vec3 gravity{ glm::vec3(0, -9.81, 0) };

	void PhysicsSystem::Step(float delta_time, Scene* scene)
	{
		//ResolveCollisions(deltaTime, scene);

		for (EntityID entity : SceneView<Transform, Rigidbody>(*scene))
		{
			Rigidbody* rigidbody = scene->GetComponent<Rigidbody>(entity);
			Transform* transform = scene->GetComponent<Transform>(entity);

			// Apply gravity
			if (rigidbody->is_dynamic)
			{
				rigidbody->force += rigidbody->mass * gravity;

				rigidbody->velocity += (rigidbody->force / rigidbody->mass) * delta_time;
				transform->SetPosition(transform->GetPosition() + (rigidbody->velocity * delta_time));

				rigidbody->force = glm::vec3();
			}
		}
	}

	void PhysicsSystem::ResolveCollisions(float delta_time, Scene* scene)
	{
		for (EntityID entity_a : SceneView<Transform, Collider>(*scene))
		{
			Transform* transform_a = scene->GetComponent<Transform>(entity_a);
			Collider* collider_a = scene->GetComponent<Collider>(entity_a);

			for (EntityID entity_b : SceneView<Transform, Collider>(*scene))
			{
				if (entity_a == entity_b)
				{
					break;
				}

				Transform* transform_b = scene->GetComponent<Transform>(entity_b);
				Collider* collider_b = scene->GetComponent<Collider>(entity_b);

				CollisionPoints points = collider_a->TestCollision(transform_a, collider_b, transform_b);

				if (points.has_collided)
				{

				}
			}
		}
	}
}