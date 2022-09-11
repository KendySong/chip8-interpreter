#include "Menu.hpp"

void Menu::HandleInterface()
{
    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("File"))
    {
        if (ImGui::MenuItem("Load"))
        {

        }

        if (ImGui::MenuItem("Save"))
        {

        }

        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Settings"))
    {
        ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
}
