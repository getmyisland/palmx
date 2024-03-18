/*******************************************************************************************
*
*   palmx example - getting started
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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cmath>

// To simplify things use the palmx namespace
using namespace palmx;

int main()
{
	Init("getting started in palmx", 1280, 720); // Create window and initialize OpenGL

	const float movement_speed = 3.5f;
	const float mouse_sensitivity = 0.1f;

	Camera camera; // Create a camera that will render the game

	Primitive cube = CreateCube();
	cube.transform.position = glm::vec3(5, 0, 0); // Set the cube's position in front of the initial camera position
	cube.color = color_red;

	LockCursor();
	SetBackground(color_black);

	while (!IsExitRequested()) // Main game loop
	{
		if (IsKeyPressed(input::Escape))
		{
			RequestExit();
		}

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

		// Zoom (FOV)
		glm::vec2 mouse_wheel_input = GetMouseWheelOffset();
		camera.zoom -= mouse_wheel_input.y;
		if (camera.zoom < 0.1f)
		{
			camera.zoom = 0.1f;
		}

		float color_speed = 1.0f;

		// Change the color of the cube using the sine function to smoothly interpolate between colors
		cube.color.r = 0.5f * (1.0f + std::sin(color_speed * GetTime()));
		cube.color.g = 0.5f * (1.0f + std::sin(color_speed * GetTime() + 2.0f));
		cube.color.b = 0.5f * (1.0f + std::sin(color_speed * GetTime() + 4.0f));

		// Rotate the cube
		float rotation_speed = 1000.0f;
		cube.transform.rotation.x = glm::radians(rotation_speed * GetTime());
		cube.transform.rotation.y = glm::radians(rotation_speed * GetTime() + 2.0f);
		cube.transform.rotation.z = glm::radians(rotation_speed * GetTime() + 4.0f);

		BeginDrawing(camera); // Begin drawing by setting up the render texture

		DrawPrimitive(cube); // Draw the spinning cube

		Dimension window_dimension = GetWindowDimension();
		// Calculate how the text needs to be positioned to be in the center of the screen
		// 48 = width/height of character
		// 12 = total characters in "Hello palmx!"
		glm::vec2 text_position = glm::vec2((window_dimension.width / 2) - ((48 * 12) / 2), (window_dimension.height / 2) - (48 / 2));
		DrawString("Hello palmx!", text_position, 1.5f);

		EndDrawing(); // End drawing by rendering the render texture onto the screen and swapping the buffers
	}

	Exit(); // Close window and OpenGL context

	return 0;
}