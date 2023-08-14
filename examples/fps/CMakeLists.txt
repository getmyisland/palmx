link_libraries(palmx)

add_executable(fps
	fps_controller.cpp
	main.cpp
	target_dummy.cpp
)

target_include_directories(fps PRIVATE "${PALMX_SOURCE_DIR}/external")