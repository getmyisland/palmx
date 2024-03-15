# Create executable target for getting_started example
add_executable(getting_started getting_started.cpp)
target_link_libraries(getting_started PRIVATE palmx)

# Create executable target for fps example
add_executable(fps fps.cpp)
target_link_libraries(fps PRIVATE palmx)

# Copying resources folder
add_custom_command(TARGET getting_started POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_CURRENT_SOURCE_DIR}/resources/
	$<TARGET_FILE_DIR:getting_started>/resources/
	COMMENT "Copying resources"
)
