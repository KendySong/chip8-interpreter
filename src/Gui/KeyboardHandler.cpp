#include "KeyboardHandler.hpp"

KeyboardHandler::KeyboardHandler()
{
    _buttonSize = ImVec2(45, 45);
}

void KeyboardHandler::HandleInterface()
{
    ImGui::Begin("Keyboard");

    ImGui::End();
}