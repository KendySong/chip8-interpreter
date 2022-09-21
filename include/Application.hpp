#include <vector>

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "CPU.hpp"
#include "../Chip8/Timer.hpp"

#include "Gui/ConsoleLog.hpp"
#include "Gui/CpuInfo.hpp"
#include "Gui/Disassembler.hpp"
#include "Gui/KeyboardHandler.hpp"
#include "Gui/MemoryViewer.hpp"
#include "Gui/Menu.hpp"
#include "Gui/Screen.hpp"
#include "Gui/StackViewer.hpp"

#include "Shader.hpp"

#include "Settings.hpp"

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
    //Attributes and properties
    static Application* _application;
    GLFWwindow* _window;

    unsigned int _fps;
    Timer _timer;

    //Instance gui components
    std::vector<Gui*> _guiComponents;
    CpuInfo _cpuInfo;
    Disassembler _disassembler;
    KeyboardHandler _keyboardHandler;
    MemoryViewer _memoryViewer;
    Menu _menu;
    Screen _screen;
    StackViewer _stackViewer;
};