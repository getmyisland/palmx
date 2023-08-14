set(PALMX_EXTERNAL_DIR "external")

set(PALMX_SOURCES 
	algo.cpp
	engine.cpp
	entity.cpp
	gui_system.cpp
	input.cpp
	input_system.cpp
	logger.cpp
	mesh.cpp
	model.cpp
	physics_system.cpp
	render_system.cpp
	resource_loader.cpp
	scene.cpp
	scene_manager.cpp
	shader.cpp
	transform.cpp
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
		${PALMX_SOURCE_DIR}/${PALMX_EXTERNAL_DIR}/glfw-3.3.8/include # Include GLFW headers
		${PALMX_SOURCE_DIR}/${PALMX_EXTERNAL_DIR}/glm # Include glm headers
		${PALMX_SOURCE_DIR}/${PALMX_EXTERNAL_DIR}/assimp/include # Include assimp headers
)

target_link_libraries(palmx 
	PUBLIC
		glfw
		OpenGL::GL
		glm
		assimp
)