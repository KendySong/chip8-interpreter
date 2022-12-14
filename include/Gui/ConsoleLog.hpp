#include <fstream>
#include <sstream>

#include <FileBrowser/ImGuiFileBrowser.h>

#include "Gui.hpp"

#include "Settings.hpp"

#pragma once
/**
 * @brief Receive and display logs
 * 
 */
class ConsoleLog : public Gui
{
private :
    /**
     * @brief Constructor
     * 
     */
    ConsoleLog() = default;

public :
    /**
     * @brief Get the Instance object
     * 
     * @return Pointer to the only instance of this class
     */
    static ConsoleLog* GetInstance();

    /**
     * @brief Display console logs
     * 
     */
    void HandleInterface();

    /**
     * @brief Add a log into the log window
     * 
     * @param log to add
     */
    void AddLog(const char* log);

    /**
     * @brief Save the current logs into txt file
     * 
     */
    void SaveToFile();

private :
    static ConsoleLog* _consoleLog;

    std::stringstream _stream;
    ImGuiTextBuffer _addressBuffer;
    imgui_addons::ImGuiFileBrowser _fileDialog;
};