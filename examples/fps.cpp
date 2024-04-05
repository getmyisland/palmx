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

static Model target_dummy;
static bool move_left = true;
static const float move_speed = 250.0f;

static Sprite bullet_sprite;
static Camera camera;

static const float movement_speed = 3.5f;
static const float mouse_sensitivity = 0.1f;

int main()
{
	Init("palmx fps example", 1280, 720);

	LockCursor();
	SetBackground(color_skyblue);

	target_dummy = LoadModel(GetResourceDir() + "/fps/models/target_dummy.obj");

	bullet_sprite.texture = LoadTexture(GetResourceDir() + "/fps/sprites/bullet.png");
	bullet_sprite.transform.position = glm::vec3(50.0f, 45.0f, 0.0f);
	bullet_sprite.transform.scale = glm::vec3(50.0f);

	while (!IsExitRequested())
	{
		if (IsKeyPressed(key::Escape))
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

	if (IsKeyPressed(key::W))
	{
		camera.transform.position += Vector3Forward(camera.transform.rotation) * velocity;
	}
	if (IsKeyPressed(key::S))
	{
		camera.transform.position -= Vector3Forward(camera.transform.rotation) * velocity;
	}
	if (IsKeyPressed(key::A))
	{
		camera.transform.position -= Vector3Right(camera.transform.rotation) * velocity;
	}
	if (IsKeyPressed(key::D))
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
	auto& transform = target_dummy.transform;

	if (move_left) {
		target_dummy.transform.position.x -= move_speed * GetDeltaTime();
	}
	else {
		target_dummy.transform.position.x += move_speed * GetDeltaTime();
	}

	// Reverse direction when reaching the end
	if (target_dummy.transform.position.x <= -8.0f) {
		move_left = false;
	}
	else if (target_dummy.transform.position.x >= 8.0f) {
		move_left = true;
	}
}

static void RenderGame()
{
	BeginDrawing(camera);

	DrawModel(target_dummy);

	DrawSprite(bullet_sprite);
	DrawString("Ammo: 69", glm::vec2(100.0f, 25.0f), 1.0f);

	EndDrawing();
}