#include <fstream>
#include <sstream>

#include <FileBrowser/ImGuiFileBrowser.h>

#include "Gui.hpp"

#pragma once

/**
 * @brief Display menu and load files
 * 
 */
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

    /**
     * @brief Display file dialog and load file,
     * if fail log error into console
     */
    void ManageFileLoading();

private :
    bool _isOpen;
    const char* _fileDialogName;
    imgui_addons::ImGuiFileBrowser _fileDialog;

    std::ifstream _fileReader;
    std::stringstream _fileStream;
};

