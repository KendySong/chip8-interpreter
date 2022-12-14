#include "Menu.hpp"

Menu::Menu()
{
    _fps = 0;
    _isOpen = false;
    _fileDialogName = "Load source code";

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
    
    ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 75);
    ImGui::Text("FPS : %i", _fps);

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
    if (_fileDialog.showFileDialog(_fileDialogName, imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(700, 500)))
    {
        _fileReader.open(_fileDialog.selected_path.c_str(), std::ios::binary | std::ios::ate);
        if (_fileReader.is_open())
        {
            std::streampos size = _fileReader.tellg();
            char* buffer = new char[size];
            _fileReader.seekg(0, std::ios::beg);
            _fileReader.read(buffer, size);
            _fileReader.close();

            for (size_t i = 0; i < size; i++)
            {
                CPU::GetInstance()->GetMemory()[Chip8::PROGRAM_START_LOC + i] = buffer[i];             
            }
                       
            delete[] buffer;
            std::string log = "[INFO] " + _fileDialog.selected_path + " loaded\n";
            ConsoleLog::GetInstance()->AddLog(log.c_str());       
        }
        else
        {
            std::string log = "[ERROR] " + _fileDialog.selected_path + " cannot be opened\n";
            ConsoleLog::GetInstance()->AddLog(log.c_str());
        }

        _isOpen = false;
    }
}

void Menu::SetFPS(int fps)
{
    _fps = fps;
}