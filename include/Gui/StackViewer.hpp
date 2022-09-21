#include "Gui.hpp"

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