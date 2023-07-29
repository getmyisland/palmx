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

void DemoController::Update(EntityID entity_id, float delta_time)
{
	Scene* scene = Engine::GetSingletonPtr()->scene_manager->GetActiveScene();
	Transform* transform = scene->GetComponent<Transform>(entity_id);
	float velocity = movement_speed_ * delta_time;

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

	glm::vec2 mouse_input = Input::GetMouseOffset();
	mouse_input.x *= mouse_sensitivity_;
	mouse_input.y *= mouse_sensitivity_;

	transform->SetRotation(transform->GetRotation() + glm::vec3(mouse_input.x, mouse_input.y, 0));

	// Make sure that when x-Rotation is out of bounds, the screen doesn't get flipped
	if (transform->GetRotation().x > 89.0f)
	{
		transform->SetRotation(glm::vec3(89.0f, transform->GetRotation().y, transform->GetRotation().z));
	}
	if (transform->GetRotation().x < -89.0f)
	{
		transform->SetRotation(glm::vec3(-89.0f, transform->GetRotation().y, transform->GetRotation().z));
	}

	render::Camera* camera = scene->GetComponent<render::Camera>(entity_id);
	if (camera != nullptr)
	{
		glm::vec2 mouse_wheel_input = Input::GetMouseWheelOffset();

		camera->zoom -= mouse_wheel_input.y;
		if (camera->zoom < 0.1f)
		{
			camera->zoom = 0.1f;
		}
	}
}