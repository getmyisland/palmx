#include "scp_173.h"

#include "../engine/Engine.h"
#include "../engine/Scene.h"
#include "../engine/Logger.h"

#include <glm/gtx/string_cast.hpp>

void SCP_173::Update(palmx::EntityID entityId, float deltaTime)
{
	palmx::Scene* scene = palmx::Engine::GetSingletonPtr()->mSceneManager->GetActiveScene();

	palmx::Transform* transform = scene->GetComponent<palmx::Transform>(entityId);
	if (transform != nullptr)
	{
		LOG_INFO("Position: " + glm::to_string(transform->GetPosition()));
	}
}
