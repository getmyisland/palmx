# palmx

A simple open source game library written in C++ that emulates some of the limitations of Sony's PlayStation 1.

## Features

- No external dependencies (all required libraries are [bundled into palmx](https://github.com/getmyisland/palmx/tree/main/external))
- Cross-Platform compatibility (Windows, Linux, MaxOS)
- Streamlined font/sprite/model rendering
- Authentic pixelated resolution (native 320x240 downscaling)

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

A step by step guide on how to integrate palmx into your game project using [CMake](https://cmake.org/download/).

```
# Clone the palmx repository into your dependency folder (e.g. external).
$ git clone https://github.com/getmyisland/palmx.git

# Navigate into the palmx folder
$ cd palmx

# Initialize submodules
$ git submodule update --init --recursive
```

Create a `CMakeLists.txt` in the root of your project.

```
# CMake version 3.15 or higher is required
cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(your_project)

# Add palmx as a subdirectory
add_subdirectory(path/to/palmx)

find_package(OpenGL REQUIRED)

# Add your source files here
add_executable(your_project main.cpp)

target_link_libraries(your_project PRIVATE palmx)

target_include_directories(your_project PRIVATE
	${PALMX_SOURCE_DIR}/${PALMX_EXTERNAL_DIR}/
    ${PALMX_SOURCE_DIR}/${PALMX_EXTERNAL_DIR}/glfw/include
    ${PALMX_SOURCE_DIR}/${PALMX_EXTERNAL_DIR}/glm
    ${PALMX_SOURCE_DIR}/${PALMX_EXTERNAL_DIR}/assimp/include
    ${PALMX_SOURCE_DIR}/${PALMX_EXTERNAL_DIR}/freetype/include
)
```

Create a `main.cpp` file in the root of your project and copy-paste the example window code from above.

Open a command line in the root of your project:

```
# Generate build files and folder
$ cmake -B build

# Build the game
$ cmake --build build
```

## Built With

- [OpenGL](https://www.opengl.org/) - Graphics Library
- [CMake](https://cmake.org/) - Build Tool
- [GLFW](https://www.glfw.org/) - Window Management
- [GLM](https://github.com/g-truc/glm) - Mathematics Library
- [assimp](https://github.com/assimp/assimp) - 3D Model Loading
- [FreeType](https://freetype.org/) - Font Loading
- [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h) - Texture Loading

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

- [Joey de Vries](https://learnopengl.com/About)
- [raysan5](https://github.com/raysan5/raylib)
