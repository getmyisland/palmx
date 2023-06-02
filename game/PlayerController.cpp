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
		transform.mPosition = transform.mPosition + (transform.mForward * velocity);
	}

	if (Input::GetKey(KEY_ARROW_DOWN))
	{
		transform.mPosition = transform.mPosition - (transform.mForward * velocity);
	}

	if (Input::GetKey(KEY_ARROW_LEFT))
	{
		transform.mPosition = transform.mPosition - (transform.mRight * velocity);
	}

	if (Input::GetKey(KEY_ARROW_RIGHT))
	{
		transform.mPosition = transform.mPosition + (transform.mRight * velocity);
	}

	glm::vec2 mouseInput = Input::GetAxis(AXIS_MOUSE);
	mouseInput.x *= _mouseSensitivity;
	mouseInput.y *= _mouseSensitivity;

	transform.mRotation = transform.mRotation + glm::vec3(mouseInput.x, mouseInput.y, 0);

	// Make sure that when x-Rotation is out of bounds, the screen doesn't get flipped
	if (transform.mRotation.x > 89.0f)
	{
		transform.mRotation = glm::vec3(89.0f, transform.mRotation.y, transform.mRotation.z);
	}
	if (transform.mRotation.x < -89.0f)
	{
		transform.mRotation = glm::vec3(-89.0f, transform.mRotation.y, transform.mRotation.z);
	}
}