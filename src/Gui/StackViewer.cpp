#include "StackViewer.hpp"

void StackViewer::HandleInterface()
{
    std::array<std::uint16_t, Chip8::REGISTER_SIZE> stack = CPU::GetInstance()->GetStack();
    ImGui::Begin("Stack");
    ImGui::Text("SP : %X", CPU::GetInstance()->GetSP());
    ImGui::Separator();

    ImGui::Columns(2);

    for (size_t i = 0; i < Chip8::REGISTER_SIZE; i++)
    {
        ImGui::Text("Stack[%X] : %X", i, stack[i]);
        ImGui::NextColumn();
    }
    

    ImGui::End();
}