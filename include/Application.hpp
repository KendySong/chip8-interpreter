#include <vector>

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "Shader.hpp"
#include "Settings.hpp"

#include "Gui/ConsoleLog.hpp"
#include "Gui/CpuInfo.hpp"
#include "Gui/InstructionDebug.hpp"
#include "Gui/KeyboardHandler.hpp"
#include "Gui/MemoryViewer.hpp"
#include "Gui/Menu.hpp"
#include "Gui/Screen.hpp"

#pragma once

/**
 * @brief Manage application running
 * 
 */
class Application
{
private :
    /**
     * @brief Create window and load opengl
     * 
     */
    Application();

public :
    /**
     * @brief Get the Instance the application
     * 
     * @return pointer to app instance
     */
    static Application* GetInstance() noexcept;
    
    /**
     * @brief Run the application
     * 
     * @return exit status
     */
    int Run();

private :
    /**
     * @brief Create new frame for imgui, 
     * draw gui and get input
     */
    void RenderGui();

    //Attributes and properties
    static Application* _application;
    GLFWwindow* _window;  

    //Instance gui components
    std::vector<Gui*> _guiComponents;
    CpuInfo _cpuInfo;
    InstructionDebug _instructionDebug;
    KeyboardHandler _keyboardHandler;
    MemoryViewer _memoryViewer;
    Menu _menu;
    Screen _screen;
};