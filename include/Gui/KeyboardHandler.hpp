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
    KeyboardHandler();

    /**
     * @brief Render the keyboard and 
     * get input from the user
     */
    void HandleInterface();
private :
    ImVec2 _buttonSize;
};