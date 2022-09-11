#include "Gui.hpp"

#pragma once

/**
 * @brief Display keyboard and get input
 * 
 */
class KeyboardHandler : public Gui
{
public :
    /**
     * @brief Constructor
     * 
     */
    KeyboardHandler() = default;

    /**
     * @brief Render the keyboard and 
     * get input from the user
     */
    void HandleInterface();
private :

};