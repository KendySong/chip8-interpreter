#include "Gui.hpp"

#include "../Chip8/CPU.hpp"

#pragma once

/**
 * @brief Display instructions of the chip8 code
 * and their addresses
 */
class InstructionDebug : public Gui
{
public :
    /**
     * @brief Construct a new Instruction Debug object
     * 
     */
    InstructionDebug() = default;

    /**
     * @brief Render instructions of the chip8 code 
     * and their addresses 
     */
    void HandleInterface();
private :
};