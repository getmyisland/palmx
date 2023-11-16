/*******************************************************************************************
*
*   palmx example - getting started
*
*   Copyright (c) 2023 Maximilian Fischer (getmyisland)
*
*   Licensed under the MIT License. See LICENSE.md for full details.
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
    Init("getting started in palmx", 1280, 720);

    const float movement_speed = 3.5f;
    const float mouse_sensitivity = 0.1f;

    // Lock the cursor so that you can look around better
    LockCursor();

    Camera camera; // Create a camera that will render the game

    Primitive cube = CreateCube();
    cube.transform.position = glm::vec3(5, 0, 0);
    cube.color = color_red;

    SetBackground(color_black); // Set a background color
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
        BeginDrawing(camera); // Initialize the rendering by setting up the render texture

        DrawPrimitive(cube);

        Dimension window_dimension = GetWindowDimension();
        DrawText("Hello palmx", 25.0f, window_dimension.height - 75.0f, 1.5f, color_white); // Draw a text in the upper left corner

        EndDrawing(); // Render the render texture onto the screen and swap the buffers
        //----------------------------------------------------------------------------------
    }
    //--------------------------------------------------------------------------------------

    // De-Initialization
    //--------------------------------------------------------------------------------------
    Exit(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}