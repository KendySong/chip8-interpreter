#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <glfw/glfw3.h>

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