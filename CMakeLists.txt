cmake_minimum_required(VERSION 3.23)
project(chip8-interpreter)

file (GLOB_RECURSE SOURCE 
    src/*.cpp 
    libraries/glad/src/*.c
)

add_executable(${PROJECT_NAME} ${SOURCE})
include_directories(include)

add_subdirectory(
    libraries/glfw
    libraries/glm
)

target_include_directories(${PROJECT_NAME}
    PRIVATE libraries/glfw/include 
    PRIVATE libraries/glad/include
    PRIVATE libraries/glm
) 

target_link_directories(${PROJECT_NAME}
    PRIVATE libraries/glfw
    PRIVATE libraries/glad
    PRIVATE libraries/glm
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE glfw
    PRIVATE glm_shared
)

#config imgui, glm