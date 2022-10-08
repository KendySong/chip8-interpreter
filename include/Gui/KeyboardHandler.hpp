#include <stdio.h>

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
    /**
     * @brief Display a button and change color depending of if he is pressed
     * 
     * @param text to display in the button
     * @param keyCode enum value of imgui about keys
     */
    void DisplayButton(const char* text, unsigned int keyCode) noexcept;

    ImVec2 _buttonSize;
};