cmake_minimum_required (VERSION 3.2)

project (CMAKE_DEMO)

set(SRC main.cpp)

message(STATUS "this is binary dir: " ${CMAKE_DEMO_BINARY_DIR})
message(STATUS "this is source dir: " ${CMAKE_DEMO_SOURCE_DIR})

add_executable(main_exe ${SRC})
