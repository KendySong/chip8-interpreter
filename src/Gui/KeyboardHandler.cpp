#include "KeyboardHandler.hpp"

KeyboardHandler::KeyboardHandler()
{
    _buttonSize = ImVec2(62, 62);
}

void KeyboardHandler::HandleInterface()
{
    ImGui::Begin("Keyboard");

    DisplayButton("1", ImGuiKey_1);
    ImGui::SameLine();
    DisplayButton("2", ImGuiKey_2);
    ImGui::SameLine();
    DisplayButton("3", ImGuiKey_3);
    ImGui::SameLine();
    DisplayButton("4", ImGuiKey_4); 
  
    DisplayButton("Q", ImGuiKey_Q);
    ImGui::SameLine();
    DisplayButton("W", ImGuiKey_W);
    ImGui::SameLine();
    DisplayButton("E", ImGuiKey_E);
    ImGui::SameLine();
    DisplayButton("R", ImGuiKey_R);

    DisplayButton("A", ImGuiKey_A);
    ImGui::SameLine();
    DisplayButton("S", ImGuiKey_S);
    ImGui::SameLine();
    DisplayButton("D", ImGuiKey_D);
    ImGui::SameLine();
    DisplayButton("F", ImGuiKey_F);

    DisplayButton("Z", ImGuiKey_Z);
    ImGui::SameLine();
    DisplayButton("X", ImGuiKey_X);
    ImGui::SameLine();
    DisplayButton("C", ImGuiKey_C);
    ImGui::SameLine();
    DisplayButton("V", ImGuiKey_V);
      
    ImGui::End();
}

void KeyboardHandler::DisplayButton(const char* text, unsigned int keyCode) noexcept
{
    if (ImGui::IsKeyDown(keyCode))
    {
        ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyle().Colors[ImGuiCol_ButtonActive]);
        ImGui::Button(text, _buttonSize);
        ImGui::PopStyleColor();
    }
    else
    {
        ImGui::Button(text, _buttonSize);
    }
}