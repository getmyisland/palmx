set(PALMX_EXTERNAL_DIR "external")

add_library(palmx)

target_compile_features(palmx PRIVATE cxx_std_20)

find_package(OpenGL REQUIRED)

target_include_directories(palmx
    PUBLIC
        $<BUILD_INTERFACE:${PALMX_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
		${PALMX_SOURCE_DIR}/include
        ${PALMX_SOURCE_DIR}/${PALMX_EXTERNAL_DIR}/
        ${PALMX_SOURCE_DIR}/${PALMX_EXTERNAL_DIR}/glfw/include
        ${PALMX_SOURCE_DIR}/${PALMX_EXTERNAL_DIR}/glm
        ${PALMX_SOURCE_DIR}/${PALMX_EXTERNAL_DIR}/assimp/include
        ${PALMX_SOURCE_DIR}/${PALMX_EXTERNAL_DIR}/freetype/include
)

target_sources(palmx PRIVATE
    palmx_core.cpp
    palmx_debug.cpp
    palmx_filesystem.cpp
    palmx_graphics.cpp
    palmx_ui.cpp
    palmx_input.cpp
    palmx_math.cpp
    ${PALMX_SOURCE_DIR}/${PALMX_EXTERNAL_DIR}/glad/glad.c
)

target_link_libraries(palmx 
	PUBLIC
		glfw
		OpenGL::GL
		glm
		assimp
		freetype
)