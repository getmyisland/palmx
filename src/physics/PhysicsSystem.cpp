#include "PhysicsSystem.h"

#include "Rigidbody.h"
#include "../engine/Scene.h"
#include "../engine/SceneView.h"
#include "../engine/Transform.h"

#include <glm/vec3.hpp>

namespace palmx
{
	const glm::vec3 GRAVITY{ glm::vec3(0, -9.81, 0) };

	void PhysicsSystem::Step(float deltaTime, Scene* scene)
	{
		for (EntityID entity : SceneView<Transform, Rigidbody>(*scene))
		{
			Rigidbody* rigidbody = scene->GetComponent<Rigidbody>(entity);
			Transform* transform = scene->GetComponent<Transform>(entity);

			// Apply a force
			rigidbody->mForce += rigidbody->mMass * GRAVITY;

			rigidbody->mVelocity += (rigidbody->mForce / rigidbody->mMass) * deltaTime;
			transform->SetPosition(transform->GetPosition() + (rigidbody->mVelocity * deltaTime));

			rigidbody->mForce = glm::vec3();
		}
	}
}