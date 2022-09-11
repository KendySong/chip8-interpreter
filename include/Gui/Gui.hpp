#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#pragma once

/**
 * @brief Interface for gui components,
 * HandleInterface is called on derived classes
 */
class Gui
{
public :
    /**
     * @brief Draw and get user input for derived class
     * 
     */
    virtual void HandleInterface() = 0;
};