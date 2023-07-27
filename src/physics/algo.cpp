#include "algo.h"

#include "collider.h"
#include "../engine/transform.h"

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

namespace palmx::physics::algo
{
	CollisionPoints FindSphereSphereCollisionPoints(const SphereCollider* a, const Transform* ta, const SphereCollider* b, const Transform* tb)
	{
		glm::vec3 centerA = ta->GetPosition() + a->mCenter;
		glm::vec3 centerB = tb->GetPosition() + b->mCenter;

		glm::vec3 distanceVec = centerB - centerA;
		float distance = glm::length(distanceVec);

		float sumRadius = a->mRadius + b->mRadius;

		if (distance <= sumRadius)
		{
			glm::vec3 collisionNormal = glm::normalize(distanceVec);
			float collisionDepth = sumRadius - distance;

			return { centerA - collisionNormal * a->mRadius, centerB - collisionNormal * b->mRadius, collisionNormal, collisionDepth, true };
		}

		return {};
	}

	CollisionPoints FindSpherePlaneCollisionPoints(const SphereCollider* a, const Transform* ta, const PlaneCollider* b, const Transform* tb)
	{
		glm::vec3 centerA = ta->GetPosition() + a->mCenter;

		float distance = glm::dot(centerA, b->mPlane) - b->mDistance;

		if (distance <= a->mRadius)
		{
			glm::vec3 collisionNormal = glm::normalize(b->mPlane);
			float collisionDepth = a->mRadius - distance;

			return { centerA - collisionNormal * a->mRadius, centerA - collisionNormal * (a->mRadius - collisionDepth), collisionNormal, collisionDepth, true };
		}

		return {};
	}

	CollisionPoints FindPlaneSphereCollisionPoints(const PlaneCollider* a, const Transform* ta, const SphereCollider* b, const Transform* tb)
	{
		// Reuse the sphere code
		CollisionPoints points = b->TestCollision(tb, a, ta);

		// Swap the points and normal
		glm::vec3 tempA = points.mA;
		points.mA = points.mB;
		points.mB = tempA;

		points.mNormal = -points.mNormal;

		return points;
	}
}