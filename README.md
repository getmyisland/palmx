# palmx

A simple open source game library written in C++ that emulates some of the limitations of Sony's PlayStation 1.

## Features

- ...

## Examples

Examples can be found in the [Examples](/examples) folder.

A basic example on how to create a window looks like this:

```c++
#include <palmx.h>

using namespace palmx;

int main() // Program Entry Point
{
	Init("hello world", 800, 600); // Create window and OpenGL context
	
	Camera camera; // A camera is always required for rendering
	
	SetBackground(color_skyblue);
	
	// Main game loop
	while(!IsExitRequested())
	{
		CollectInput(); // Gather input
		
		// TODO Update variables

        BeginDrawing(camera); // Setup render texture
		
		// TODO Draw Models/Sprites/Text
		
        EndDrawing(); // Swap buffers
	}
	
	Exit(); // Close window and OpenGL context
	
	return 0;
}
```

## Installation

A step by step guide on how to integrate palmx into your game project.

### CMake (recommended)

CMake version 3.15 or higher is required if you decide to use this approach. 

Clone the palmx repository into your dependency folder (e.g. external).

```
git clone https://github.com/getmyisland/palmx.git
```

Add palmx as a subdirectory in your `CMakeLists.txt`.

```
add_subdirectory(path/to/palmx)
```

Link required dependencies in your `CMakeLists.txt`.

```
find_package(OpenGL REQUIRED)

target_link_libraries(your_project PRIVATE palmx)

target_include_directories(your_project PRIVATE
	${PALMX_SOURCE_DIR}/${PALMX_EXTERNAL_DIR}/
    ${PALMX_SOURCE_DIR}/${PALMX_EXTERNAL_DIR}/glfw/include
    ${PALMX_SOURCE_DIR}/${PALMX_EXTERNAL_DIR}/glm
    ${PALMX_SOURCE_DIR}/${PALMX_EXTERNAL_DIR}/assimp/include
    ${PALMX_SOURCE_DIR}/${PALMX_EXTERNAL_DIR}/freetype/include
)
```

That's it. You can now try out the example from above to check whether you have set up your project correctly.

### Manual Linking

TODO

## Built With

* [OpenGL](https://www.opengl.org/) - Graphics Library
* [CMake](https://cmake.org/) - Build Tool
* [GLFW](https://www.glfw.org/) - Window Management
* [GLM](https://github.com/g-truc/glm) - Mathematics Library
* [assimp](https://github.com/assimp/assimp) - 3D Model Loading
* [FreeType](https://freetype.org/) - Font Loading
* [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h) - Texture Loading

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* [Joey de Vries](https://learnopengl.com/About)
* [raysan5](https://github.com/raysan5/raylib)
