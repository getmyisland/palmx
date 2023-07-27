#include "demo_enemy.h"

#include "../engine/engine.h"
#include "../engine/scene.h"
#include "../engine/logger.h"
#include "../engine/scene_manager.h"

#include <glm/gtx/string_cast.hpp>

void DemoEnemy::Update(palmx::EntityID entityId, float deltaTime)
{
	palmx::Scene* scene = palmx::Engine::GetSingletonPtr()->mSceneManager->GetActiveScene();

	palmx::Transform* transform = scene->GetComponent<palmx::Transform>(entityId);
	if (transform != nullptr)
	{
		//LOG_INFO("Position: " + glm::to_string(transform->GetPosition()));
	}
}
