#include "MenuSettings.hpp"

void MenuSettings::HandleInterface()
{
    ImGui::Begin("Settings");
    ImGui::TextUnformatted("CPU speed (Instruction/ms)");
    ImGui::SameLine();
    ImGui::InputFloat(" ", &Settings::cpuSpeed);
    ImGui::End();
}