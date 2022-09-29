#include "../Chip8/Cpu.hpp"

#include "Gui.hpp"

#include "Settings.hpp"

#pragma once
/**
 * @brief Display and modify settings
 * 
 */
class Debugger : public Gui
{
public :
    /**
     * @brief Constructor
     * 
     */
    Debugger() = default;

    /**
     * @brief Display and construct the interface
     * 
     */
    void HandleInterface();
};