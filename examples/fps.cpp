/*******************************************************************************************
*
*   palmx example - fps
*
*   Copyright (c) 2023 Maximilian Fischer (getmyisland)
*
*   Licensed under the MIT License. See LICENSE.md for full details.
*
********************************************************************************************/

#include <palmx.h>
#include <palmx_math.h>

using namespace palmx;

void ProcessInput();
void RenderGame();

Model scp_173;

Camera camera;

const float movement_speed = 3.5f;
const float mouse_sensitivity = 0.1f;

int main()
{
	Init("palmx fps example", 1280, 720);

	LockCursor();
	SetBackground(color_skyblue);

	std::string root_dir = GetRootDirectory();
	scp_173 = LoadModel(root_dir + "/resources/models/scp173/cb_scp173.fbx");

	while (!IsExitRequested())
	{
		ProcessInput();

		RenderGame();
	}

	Exit();

	return 0;
}

void ProcessInput()
{
	CollectInput();

	float velocity = movement_speed * GetDeltaTime();

	if (IsKeyPressed(KeyCode::KEY_W))
	{
		camera.transform.position += Vector3Forward(camera.transform.rotation) * velocity;
	}
	if (IsKeyPressed(KeyCode::KEY_S))
	{
		camera.transform.position -= Vector3Forward(camera.transform.rotation) * velocity;
	}
	if (IsKeyPressed(KeyCode::KEY_A))
	{
		camera.transform.position -= Vector3Right(camera.transform.rotation) * velocity;
	}
	if (IsKeyPressed(KeyCode::KEY_D))
	{
		camera.transform.position += Vector3Right(camera.transform.rotation) * velocity;
	}

	glm::vec2 mouse_input = GetMouseOffset();
	mouse_input.x *= mouse_sensitivity;
	mouse_input.y *= mouse_sensitivity;

	camera.transform.rotation += glm::vec3(mouse_input.x, mouse_input.y, 0);

	// Make sure that when x-Rotation is out of bounds, the screen doesn't get flipped
	if (camera.transform.rotation.x > 89.0f)
	{
		camera.transform.rotation.x = 89.0f;
	}
	if (camera.transform.rotation.x < -89.0f)
	{
		camera.transform.rotation.x = -89.0f;
	}

	glm::vec2 mouse_wheel_input = GetMouseWheelOffset();
	camera.zoom -= mouse_wheel_input.y;
	if (camera.zoom < 0.1f)
	{
		camera.zoom = 0.1f;
	}
}

void RenderGame()
{
	BeginDrawing(camera);

	DrawModel(scp_173);

	EndDrawing();
}