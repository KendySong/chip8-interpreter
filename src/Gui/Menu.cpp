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
        _fileReader.open(_fileDialog.selected_path.c_str(), std::ios::binary | std::ios::ate);
        if (_fileReader.is_open())
        {
            std::streampos size = _fileReader.tellg();
            char* buffer = new char[size];
            _fileReader.seekg(0, std::ios::beg);
            _fileReader.read(buffer, size);
            
            //Load into mem
            for (size_t i = 0; i < size; i++)
            {
                std::cout << std::hex << "0x" << +(unsigned char)buffer[i] << "\n";
            }
            

            //delete[] buffer;
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
