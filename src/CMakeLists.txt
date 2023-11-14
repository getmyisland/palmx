set(PALMX_EXTERNAL_DIR "external")

set(PALMX_SOURCES 
	palmx_core.cpp
	palmx_debug.cpp
	palmx_filesystem.cpp
	palmx_graphics.cpp
	palmx_ui.cpp
	palmx_input.cpp
	palmx_math.cpp
	${CMAKE_SOURCE_DIR}/${PALMX_EXTERNAL_DIR}/glad/glad.c # Add glad.c or else OpenGL won't work
)

add_library(palmx STATIC ${PALMX_SOURCES})

find_package(OpenGL REQUIRED)

target_include_directories(palmx
    PUBLIC
        $<BUILD_INTERFACE:${PALMX_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
		${PALMX_SOURCE_DIR}/include
        ${PALMX_SOURCE_DIR}/${PALMX_EXTERNAL_DIR}
		${PALMX_SOURCE_DIR}/${PALMX_EXTERNAL_DIR}/glfw/include # Include GLFW headers
		${PALMX_SOURCE_DIR}/${PALMX_EXTERNAL_DIR}/glm # Include glm headers
		${PALMX_SOURCE_DIR}/${PALMX_EXTERNAL_DIR}/assimp/include # Include assimp headers
		${PALMX_SOURCE_DIR}/${PALMX_EXTERNAL_DIR}/assimp/include # Include freetype headers
)

target_link_libraries(palmx 
	PUBLIC
		glfw
		OpenGL::GL
		glm
		assimp
		freetype
)