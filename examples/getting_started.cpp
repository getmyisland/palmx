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

    Camera camera; // Create a camera that will render the game

    SetBackground(color_darkbrown); // Set a background color
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
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Graphics
        //----------------------------------------------------------------------------------
        BeginDrawing(camera);

        // TODO spinning cube
        // TODO change color over time

        Dimension window_dimension = GetWindowDimension();
        DrawText("Hello palmx", (window_dimension.width / 2) - (12 * 32), (window_dimension.heigth / 2) - 32, 2.0f, color_white);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    //--------------------------------------------------------------------------------------

    // De-Initialization
    //--------------------------------------------------------------------------------------
    Exit(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}