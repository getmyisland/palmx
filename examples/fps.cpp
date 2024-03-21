/*******************************************************************************************
*
*   palmx example - fps
*
*	MIT License
*
*   Copyright (c) 2023 Maximilian Fischer (getmyisland)
*
*   Permission is hereby granted, free of charge, to any person obtaining a copy
*   of this software and associated documentation files (the "Software"), to deal
*   in the Software without restriction, including without limitation the rights
*   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*   copies of the Software, and to permit persons to whom the Software is
*   furnished to do so, subject to the following conditions:
*
*   The above copyright notice and this permission notice shall be included in all
*   copies or substantial portions of the Software.
*
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*   SOFTWARE.
*
********************************************************************************************/

#include <palmx.h>
#include <palmx_math.h>

using namespace palmx;

static void ProcessInput();
static void UpdateTargetPosition();
static void RenderGame();

static Model scp_173;
static bool move_left = true;
static const float move_speed = 250.0f;

static Texture bullet_sprite;
static Camera camera;

static const float movement_speed = 3.5f;
static const float mouse_sensitivity = 0.1f;

int main()
{
	Init("palmx fps example", 1280, 720);

	LockCursor();
	SetBackground(color_skyblue);

	scp_173 = LoadModel(GetResourceDir() + "/fps/models/scp173/cb_scp173.fbx");
	bullet_sprite = LoadTexture(GetResourceDir() + "/fps/sprites/bullet.png");

	while (!IsExitRequested())
	{
		if (IsKeyPressed(input::Escape))
		{
			RequestExit();
		}

		ProcessInput();
		UpdateTargetPosition();
		RenderGame();
	}

	Exit();

	return 0;
}

static void ProcessInput()
{
	float velocity = movement_speed * GetDeltaTime();

	if (IsKeyPressed(input::W))
	{
		camera.transform.position += Vector3Forward(camera.transform.rotation) * velocity;
	}
	if (IsKeyPressed(input::S))
	{
		camera.transform.position -= Vector3Forward(camera.transform.rotation) * velocity;
	}
	if (IsKeyPressed(input::A))
	{
		camera.transform.position -= Vector3Right(camera.transform.rotation) * velocity;
	}
	if (IsKeyPressed(input::D))
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

static void UpdateTargetPosition()
{
	auto& transform = scp_173.transform;

	if (move_left) {
		scp_173.transform.position.x -= move_speed * GetDeltaTime();
	}
	else {
		scp_173.transform.position.x += move_speed * GetDeltaTime();
	}

	// Reverse direction when reaching the end
	if (scp_173.transform.position.x <= -8.0f) {
		move_left = false;
	}
	else if (scp_173.transform.position.x >= 8.0f) {
		move_left = true;
	}
}

static void RenderGame()
{
	BeginDrawing(camera);

	DrawModel(scp_173);

	DrawSprite(bullet_sprite, glm::vec2(50.0f, 45.0f), glm::vec2(50.0f, 50.0f));
	DrawString("Ammo: 69", glm::vec2(100.0f, 25.0f), 1.0f);

	EndDrawing();
}