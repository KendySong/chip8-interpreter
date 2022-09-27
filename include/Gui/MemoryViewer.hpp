#include <vector>
#include <stdio.h>
#include <cstdint>
#include <string>

#include "Gui.hpp"

#include "Settings.hpp"

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

    /**
     * @brief Get the instance the application
     * 
     * @return pointer to memory viewer instance
     */
    static MemoryViewer* GetInstance();

    /**
     * @brief Store the rom bytes for display
     * 
     * @return vector that store rom bytes
     */
    std::vector<std::uint8_t>& GetMemoryRom() noexcept;

private :
    static MemoryViewer* _memoryViewer;
    std::vector<std::uint8_t> _memoryRom;
};