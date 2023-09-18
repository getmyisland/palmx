#include "fps_controller.h"

#include <palmx/input.h>
#include <palmx/scene.h>
#include <palmx/engine.h>
#include <palmx/transform.h>
#include <palmx/scene_manager.h>
#include <palmx/logger.h>

#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

using namespace palmx;

void FpsController::Update(EntityID entity_id, float delta_time)
{
	Scene* scene = Engine::GetSingletonPtr()->scene_manager->GetActiveScene();
	Transform* transform = scene->GetComponent<Transform>(entity_id);

	float velocity = movement_speed_ * delta_time;

	if (Input::GetKey(GLFW_KEY_W))
	{
		transform->position += transform->rotation.Forward() * velocity;
	}

	if (Input::GetKey(GLFW_KEY_S))
	{
		transform->position -= transform->rotation.Forward() * velocity;
	}

	if (Input::GetKey(GLFW_KEY_A))
	{
		transform->position -= transform->rotation.Right() * velocity;
	}

	if (Input::GetKey(GLFW_KEY_D))
	{
		transform->position += transform->rotation.Right() * velocity;
	}

	glm::vec2 mouse_input = Input::GetMouseOffset();
	mouse_input.x *= mouse_sensitivity_;
	mouse_input.y *= mouse_sensitivity_;

	transform->rotation += Vector3(mouse_input.x, mouse_input.y, 0);

	// Make sure that when x-Rotation is out of bounds, the screen doesn't get flipped
	if (transform->rotation.X() > 89.0f)
	{
		transform->rotation.X() = 89.0f;
	}
	if (transform->rotation.X() < -89.0f)
	{
		transform->rotation.X() = -89.0f;
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