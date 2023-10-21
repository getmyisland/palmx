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
#include <palmx_debug.h>

// To make things easier use the namespace
using namespace palmx;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screen_width = 1280;
    const int screen_height = 720;

    Init("getting started in palmx", screen_width, screen_height);

    Camera camera; // Create a camera that will render the game

    SetBackground(color_darkgreen); // Set a background color
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!IsExitRequested()) // Detect if exit was requested manually or by pressing the exit key (default = KEY_ESCAPE)
    {
        // Input
        //----------------------------------------------------------------------------------
        CollectInput(); // Note: Input has to be manually collected each frame

        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing(camera);



        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    Exit(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}