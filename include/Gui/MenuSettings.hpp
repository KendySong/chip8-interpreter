#include "Gui.hpp"

#include "Settings.hpp"

#pragma once
/**
 * @brief Display and modify settings
 * 
 */
class MenuSettings : public Gui
{
public :
    /**
     * @brief Constructor
     * 
     */
    MenuSettings() = default;

    /**
     * @brief Display and construct the interface
     * 
     */
    void HandleInterface();
};