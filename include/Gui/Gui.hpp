#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#pragma once
class Gui
{
public :
    /**
     * @brief Draw and get user input for derived class
     * 
     */
    virtual void HandleInterface() = 0;
};