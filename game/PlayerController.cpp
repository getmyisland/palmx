#include "PlayerController.h"

#include <input/Input.h>
#include <logging/LogManager.h>

#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

using namespace PalmEngine;

void PlayerController::Update(float deltaTime, Transform& transform)
{
	float velocity = _movementSpeed * deltaTime;

	if (Input::GetKey(KEY_ARROW_UP))
	{
		glm::vec3 up = transform.GetPosition() + (transform.GetForward() * velocity);
		transform.SetPosition(up);
	}

	if (Input::GetKey(KEY_ARROW_DOWN))
	{
		glm::vec3 down = transform.GetPosition() - (transform.GetForward() * velocity);
		transform.SetPosition(down);
	}

	if (Input::GetKey(KEY_ARROW_LEFT))
	{
		glm::vec3 left = transform.GetPosition() - (transform.GetRight() * velocity);
		transform.SetPosition(left);
	}

	if (Input::GetKey(KEY_ARROW_RIGHT))
	{
		glm::vec3 right = transform.GetPosition() + (transform.GetRight() * velocity);
		transform.SetPosition(right);
	}

	glm::vec2 mouseInput = Input::GetAxis(AXIS_MOUSE);
	mouseInput.x *= _mouseSensitivity;
	mouseInput.y *= _mouseSensitivity;

	transform.SetRotation(transform.GetRotation() + glm::vec3(mouseInput.x, mouseInput.y, 0));

	// Make sure that when x-Rotation is out of bounds, the screen doesn't get flipped
	if (transform.GetRotation().x > 89.0f)
	{
		transform.SetRotation(glm::vec3(89.0f, transform.GetRotation().y, transform.GetRotation().z));
	}
	if (transform.GetRotation().x < -89.0f)
	{
		transform.SetRotation(glm::vec3(-89.0f, transform.GetRotation().y, transform.GetRotation().z));
	}
}