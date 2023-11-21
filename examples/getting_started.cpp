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

// To make things easier use the namespace
using namespace palmx;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    Init("getting started in palmx", 1280, 720); // Create window and initialize OpenGL

    const float movement_speed = 3.5f;
    const float mouse_sensitivity = 0.1f;

    Camera camera; // Create a camera that will render the game

    Primitive cube = CreateCube(); // Create an example cube
    cube.transform.position = glm::vec3(5, 0, 0);
    cube.color = color_red;

    LockCursor(); // Lock the cursor so that you can look around better

    SetBackground(color_black);
    //--------------------------------------------------------------------------------------

    // Main game loop
    //--------------------------------------------------------------------------------------
    while (!IsExitRequested()) // Detect if exit was requested manually or by pressing the exit key (default = KEY_ESCAPE)
    {
        // Input
        //----------------------------------------------------------------------------------
        CollectInput(); // Note: Input has to be manually collected each frame
        //----------------------------------------------------------------------------------

        // Update
        //----------------------------------------------------------------------------------
        float velocity = movement_speed * GetDeltaTime();

        // Process inputs
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

        // Apply mouse input
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

        // The speed of color cycling
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
        //----------------------------------------------------------------------------------

        // Graphics
        //----------------------------------------------------------------------------------
        BeginDrawing(camera); // Begin drawing by setting up the render texture

        DrawPrimitive(cube); // Draw the spinning cube

        Dimension window_dimension = GetWindowDimension();
        // Calculate how the text needs to be positioned to be in the center of the screen
        // 48 = width/height of character
        // 12 = total characters in "Hello palmx!"
        glm::vec2 text_position = glm::vec2((window_dimension.width / 2) - ((48 * 12) / 2), (window_dimension.height / 2) - (48 / 2));
        DrawText("Hello palmx!", text_position, 1.5f);

        EndDrawing(); // End drawing by rendering the render texture onto the screen and swapping the buffers
        //----------------------------------------------------------------------------------
    }
    //--------------------------------------------------------------------------------------

    // De-Initialization
    //--------------------------------------------------------------------------------------
    Exit(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}