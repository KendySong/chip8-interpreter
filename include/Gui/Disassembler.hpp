#include <stdio.h>

#include "../Chip8/CPU.hpp"

#pragma once

/**
 * @brief Display instructions of the chip8 code
 * and their addresses
 */
class Disassembler : public Gui
{
public :
    /**
     * @brief Construct a new Instruction Debug object
     * 
     */
    Disassembler();

    /**
     * @brief Render instructions of the chip8 code 
     * and their addresses 
     */
    void HandleInterface();

private :
    void DisassembleInstruction(std::uint16_t opCode);

    bool _renderAtPC;
};