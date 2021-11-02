cmake_minimum_required(VERSION 3.20)

project(state_machine)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")

include_directories(${CMAKE_SOURCE_DIR}/Src)

aux_source_directory(${CMAKE_SOURCE_DIR}/Src srcs)

add_executable(
	demo	
	${srcs}
	Examples/demo.c
)

# https://cmake.org/cmake/help/latest/index.html
