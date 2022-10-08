#include <fstream>
#include <sstream>

#include <FileBrowser/ImGuiFileBrowser.h>

#include "../Chip8/CPU.hpp"

#include "ConsoleLog.hpp"

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

    /**
     * @brief Set the number of fps
     * 
     */
    void SetFPS(int fps);

private :
    int _fps;

    bool _isOpen;
    const char* _fileDialogName;
    imgui_addons::ImGuiFileBrowser _fileDialog;

    std::ifstream _fileReader;
    std::stringstream _fileStream;
};

