#include "Gui.hpp"

#include "../Chip8/Cpu.hpp"

#pragma once

/**
 * @brief Display the stack content
 * 
 */
class StackViewer : public Gui
{
public :
    /**
     * @brief Constructor
     * 
     */
    StackViewer() = default;

    /**
     * @brief Display stack content
     * 
     */
    void HandleInterface();

private :
};