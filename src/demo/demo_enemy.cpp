#include "demo_enemy.h"

#include "../engine/engine.h"
#include "../engine/scene.h"
#include "../engine/logger.h"
#include "../engine/scene_manager.h"

#include <glm/gtx/string_cast.hpp>

void DemoEnemy::Update(palmx::EntityID entity_id, float delta_time)
{
	palmx::Scene* scene = palmx::Engine::GetSingletonPtr()->scene_manager->GetActiveScene();

	palmx::Transform* transform = scene->GetComponent<palmx::Transform>(entity_id);
	if (transform != nullptr)
	{
		//LOG_INFO("Position: " + glm::to_string(transform->GetPosition()));
	}
}
