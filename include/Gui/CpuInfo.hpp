#include "Gui.hpp"

#pragma once

/**
 * @brief Display cpu register,
 * and other info
 */
class CpuInfo : public Gui
{
public :
    /**
     * @brief Constructor
     * 
     */
    CpuInfo() = default;

    /**
     * @brief Render the interface and
     * get from chip8 emulator
     */
    void HandleInterface();
private :
};