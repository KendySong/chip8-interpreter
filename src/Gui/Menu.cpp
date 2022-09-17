#include "Menu.hpp"

Menu::Menu()
{
    _fps = 0;
    _isOpen = false;
    _fileDialogName = "Load source code";

    for (size_t i = 0; i < Settings::fpsTextSpace; i++)
    {
        _barSpace += ' ';
    }

    CPU::GetInstance();
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

    ImGui::Text(_barSpace.c_str());
    ImGui::Text("FPS :");
    ImGui::Text(std::to_string(_fps).c_str());

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

            for (size_t i = 0; i < size; i++)
            {
                CPU::GetInstance()->GetMemory()[PROGRAM_START_LOC + i] = buffer[i];
            }
                       
            delete[] buffer;
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

void Menu::SetFPS(int fps)
{
    _fps = fps;
}