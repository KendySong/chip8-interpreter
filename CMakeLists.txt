cmake_minimum_required(VERSION 3.23)
project(chip8-interpreter)

file (GLOB_RECURSE SOURCE src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCE} libraries/glad/src/glad.c)
include_directories(include)

add_subdirectory(libraries/glfw)

target_include_directories(${PROJECT_NAME}
    PUBLIC libraries/glfw/include
    PUBLIC libraries/glad/include
) 

target_link_directories(${PROJECT_NAME}
    PRIVATE libraries/glfw/src
)

target_link_libraries(${PROJECT_NAME}
    glfw
)