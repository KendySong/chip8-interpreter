#include <glad/glad.h>
#include <glfw/glfw3.h>

//#include <glm/glm.hpp>

#include "Shader.hpp"
#include "Settings.hpp"

#pragma once
class Application
{
private :
    static Application* _application;

    GLFWwindow* _window;
    
    Application();

public :
    static Application* GetInstance() noexcept;
    
    int Run() const noexcept;
};