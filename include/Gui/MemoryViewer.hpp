#include "Gui.hpp"

#pragma once

/**
 * @brief Display the memory of the emulated program
 * 
 */
class MemoryViewer : public Gui
{
public :
    /**
     * @brief Constructor
     * 
     */
    MemoryViewer() = default;

    /**
     * @brief Render the memory and get input
     * from the user
     */
    void HandleInterface();

private :
};