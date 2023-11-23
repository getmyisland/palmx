cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(palmx)

option(PALMX_BUILD_EXAMPLES "Build example projects." ON)

set(PALMX_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(src)
add_subdirectory(external)

if(PALMX_BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()