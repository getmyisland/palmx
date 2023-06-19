#include "PlayerController.h"

#include "../engine/Input.h"
#include "../engine/Scene.h"
#include "../engine/Engine.h"
#include "../renderer/Transform.h"

#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

using namespace palmx;

void PlayerController::Update(EntityID entityId, float deltaTime)
{
	Scene* scene = Engine::GetSingletonPtr()->mSceneModule->GetActiveScene();
	Transform* transform = scene->GetComponent<Transform>(entityId);
	float velocity = _movementSpeed * deltaTime;

	if (Input::GetKey(KeyW))
	{
		glm::vec3 up = transform->GetPosition() + (transform->GetForward() * velocity);
		transform->SetPosition(up);
	}

	if (Input::GetKey(KeyS))
	{
		glm::vec3 down = transform->GetPosition() - (transform->GetForward() * velocity);
		transform->SetPosition(down);
	}

	if (Input::GetKey(KeyA))
	{
		glm::vec3 left = transform->GetPosition() - (transform->GetRight() * velocity);
		transform->SetPosition(left);
	}

	if (Input::GetKey(KeyD))
	{
		glm::vec3 right = transform->GetPosition() + (transform->GetRight() * velocity);
		transform->SetPosition(right);
	}

	glm::vec2 mouseInput = Input::GetMouseOffset();
	mouseInput.x *= _mouseSensitivity;
	mouseInput.y *= _mouseSensitivity;

	transform->SetRotation(transform->GetRotation() + glm::vec3(mouseInput.x, mouseInput.y, 0));

	// Make sure that when x-Rotation is out of bounds, the screen doesn't get flipped
	if (transform->GetRotation().x > 89.0f)
	{
		transform->SetRotation(glm::vec3(89.0f, transform->GetRotation().y, transform->GetRotation().z));
	}
	if (transform->GetRotation().x < -89.0f)
	{
		transform->SetRotation(glm::vec3(-89.0f, transform->GetRotation().y, transform->GetRotation().z));
	}
}