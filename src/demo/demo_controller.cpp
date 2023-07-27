#include "demo_controller.h"

#include "../engine/input.h"
#include "../engine/scene.h"
#include "../engine/engine.h"
#include "../engine/transform.h"
#include "../engine/scene_manager.h"
#include "../engine/logger.h"

#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

using namespace palmx;

void DemoController::Update(EntityID entityId, float deltaTime)
{
	Scene* scene = Engine::GetSingletonPtr()->mSceneManager->GetActiveScene();
	Transform* transform = scene->GetComponent<Transform>(entityId);
	float velocity = _movementSpeed * deltaTime;

	if (Input::GetKey(GLFW_KEY_W))
	{
		glm::vec3 up = transform->GetPosition() + (transform->GetForward() * velocity);
		transform->SetPosition(up);
	}

	if (Input::GetKey(GLFW_KEY_S))
	{
		glm::vec3 down = transform->GetPosition() - (transform->GetForward() * velocity);
		transform->SetPosition(down);
	}

	if (Input::GetKey(GLFW_KEY_A))
	{
		glm::vec3 left = transform->GetPosition() - (transform->GetRight() * velocity);
		transform->SetPosition(left);
	}

	if (Input::GetKey(GLFW_KEY_D))
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

	render::Camera* camera = scene->GetComponent<render::Camera>(entityId);
	if (camera != nullptr)
	{
		glm::vec2 mouseWheelInput = Input::GetMouseWheelOffset();

		camera->mZoom -= mouseWheelInput.y;
		if (camera->mZoom < 0.1f)
		{
			camera->mZoom = 0.1f;
		}
	}

	LOG_INFO("Position: " + glm::to_string(transform->GetRotation()));
}