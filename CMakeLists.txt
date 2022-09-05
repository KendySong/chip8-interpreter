cmake_minimum_required(VERSION 3.23)
project(chip8-interpreter)

file (GLOB_RECURSE SOURCE 
    src/*.cpp 
    libraries/glad/src/*.c
)

add_executable(${PROJECT_NAME} ${SOURCE})
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

#config glad, imgui, glm