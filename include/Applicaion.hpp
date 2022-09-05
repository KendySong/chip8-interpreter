#include <glad/glad.h>
#include <glfw/glfw3.h>

#pragma once
class Application
{
private :
    GLFWwindow* _window;
    static Application* _application;

    Application();

public :
    static Application* GetInstance() const noexcept;
    
    int Run() const noexcept;
};