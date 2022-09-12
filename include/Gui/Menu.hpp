#include <iostream>
#include <FileBrowser/ImGuiFileBrowser.h>

#include "Gui.hpp"

#pragma once

class Menu : public Gui
{
public :
    /**
     * @brief Constructor
     * 
     */
    Menu();

    /**
     * @brief Display main menu bar and
     * manage file dialog's winodw
     */
    void HandleInterface();

private :
    bool _isOpen;
    const char* _fileLoad;
    imgui_addons::ImGuiFileBrowser _fileDialog;
};