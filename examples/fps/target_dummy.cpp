#include "target_dummy.h"

#include <palmx/engine.h>
#include <palmx/scene.h>
#include <palmx/logger.h>
#include <palmx/scene_manager.h>

#include <glm/gtx/string_cast.hpp>

void TargetDummy::Update(palmx::EntityID entity_id, float delta_time)
{
	palmx::Scene* scene = palmx::Engine::GetSingletonPtr()->scene_manager->GetActiveScene();

	palmx::Transform* transform = scene->GetComponent<palmx::Transform>(entity_id);
	if (transform != nullptr)
	{
		// LOG_INFO("Position: " + glm::to_string(transform->GetPosition()));
	}
}
