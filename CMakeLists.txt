cmake_minimum_required(VERSION 3.23)
project(chip8-interpreter)

file (GLOB_RECURSE SOURCE src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCE})
include_directories(include)

