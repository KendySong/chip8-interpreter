#include "Menu.hpp"

Menu::Menu()
{
    _isOpen = false;
    _fileLoad = "Load source code";
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

    if (_isOpen)
    {
        ImGui::OpenPopup(_fileLoad);
        _isOpen = false;
    }

    if (_fileDialog.showFileDialog(_fileLoad, imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(700, 500), ".ch8"))
    {
        CodeLoader codeLoader;
        codeLoader.LoadSourceCode(_fileDialog.selected_path.c_str());
        _isOpen = false;
    }
}
