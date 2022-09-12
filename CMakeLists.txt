cmake_minimum_required(VERSION 3.23)
project(chip8-interpreter)

file (GLOB_RECURSE SOURCE
    src/*.cpp 
    libraries/glad/src/*.c
    libraries/ImGui/*.cpp


    libraries/FileBrowser/ImGuiFileBrowser.cpp


)

add_executable(${PROJECT_NAME} ${SOURCE})
include_directories(
    include 
    include/Chip8
    include/Render
    include/Gui
    libraries


    libraries/FileBrowser


)

add_subdirectory(libraries/glfw)
add_subdirectory(libraries/glm)

target_include_directories(${PROJECT_NAME}
    PUBLIC libraries/glfw/include 
    PUBLIC libraries/glad/include 
    PUBLIC libraries/glm
    PUBLIC libraries/FileBrowser/Dirent
)

target_link_directories(${PROJECT_NAME}
    PUBLIC libraries/glfw 
    PUBLIC libraries/glad 
    PUBLIC libraries/glm
)

target_link_libraries(${PROJECT_NAME} 
    glfw
    glm
)

file (COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_SOURCE_DIR}/build)