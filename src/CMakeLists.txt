add_library(palmx)

find_package(OpenGL REQUIRED)

target_include_directories(palmx PUBLIC
	${PALMX_SOURCE_DIR}/include
	${PALMX_SOURCE_DIR}/external/glad/include
	${PALMX_SOURCE_DIR}/external/glfw/include
	${PALMX_SOURCE_DIR}/external/assimp/include
	${PALMX_SOURCE_DIR}/external/freetype/include
	${PALMX_SOURCE_DIR}/external/glm
	${PALMX_SOURCE_DIR}/external/stb_image
)

target_sources(palmx PRIVATE
	pxpch.cpp
    palmx_core.cpp
    palmx_debug.cpp
    palmx_filesystem.cpp
    palmx_graphics.cpp
    palmx_ui.cpp
    palmx_input.cpp
    palmx_math.cpp
    ${PALMX_SOURCE_DIR}/external/glad/src/glad.c
    ${PALMX_SOURCE_DIR}/external/stb_image/stb_image.cpp
)

target_link_libraries(palmx PUBLIC
	${OPENGL_LIBRARIES}
	glfw
	glm
	assimp
	freetype
)