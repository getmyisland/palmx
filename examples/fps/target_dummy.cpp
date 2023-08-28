#include "target_dummy.h"

#include <palmx/engine.h>
#include <palmx/scene.h>
#include <palmx/logger.h>
#include <palmx/scene_manager.h>

#include <glm/gtx/string_cast.hpp>

bool going_left = true;

void TargetDummy::Update(palmx::EntityID entity_id, float delta_time)
{
	palmx::Scene* scene = palmx::Engine::GetSingletonPtr()->scene_manager->GetActiveScene();
	float movement_speed = 1.0f;
	float velocity = movement_speed * delta_time;

	palmx::Transform* transform = scene->GetComponent<palmx::Transform>(entity_id);
	if (transform != nullptr)
	{
		if (going_left)
		{
			glm::vec3 left = transform->GetPosition() - (transform->GetForward() * velocity);
			transform->SetPosition(left);

			if (transform->GetPosition().x < -5)
			{
				going_left = false;
			}
		}
		else
		{
			glm::vec3 right = transform->GetPosition() + (transform->GetForward() * velocity);
			transform->SetPosition(right);

			if (transform->GetPosition().x > 5)
			{
				going_left = true;
			}
		}
	}
}
