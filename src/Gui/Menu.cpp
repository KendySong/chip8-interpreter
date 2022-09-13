#include "Menu.hpp"

Menu::Menu()
{
    _isOpen = false;
    _fileDialogName = "Load source code";
}

void Menu::HandleInterface()
{
    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("File"))
    {
        if (ImGui::MenuItem("Load"))
        {
            _isOpen = true;
        }

        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Settings"))
    {
        ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
    ManageFileLoading();   
}

void Menu::ManageFileLoading()
{
    if (_isOpen)
    {
        ImGui::OpenPopup(_fileDialogName);
        _isOpen = false;
    }

    //Manage chip8 code loading into program
    if (_fileDialog.showFileDialog(_fileDialogName, imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(700, 500), ".ch8"))
    {
        _fileReader.open(_fileDialog.selected_path.c_str());
        if (_fileReader.is_open())
        {
            _fileStream << _fileReader.rdbuf();
            std::string log = "[INFO] " + _fileDialog.selected_path + " loaded\n";
            ConsoleLog::GetInstance()->AddLog(log.c_str());
        }
        else
        {
            std::string log = "[ERROR] " + _fileDialog.selected_path + " cannot opened\n";
            ConsoleLog::GetInstance()->AddLog(log.c_str());
        }

        _isOpen = false;
    }
}
