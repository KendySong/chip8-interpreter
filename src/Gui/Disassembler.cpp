#include "Disassembler.hpp"

void Disassembler::HandleInterface()
{
    if (ImGui::Begin("Disassembler"))
    {
        if (ImGui::Button("Start"))
        {
            CPU::GetInstance()->Run();
        }

        ImGui::SameLine();
        ImGui::Button("Step by step");
        
        ImGui::SameLine();
        if (ImGui::Button("Stop"))
        {
            CPU::GetInstance()->Pause();
        }

        ImGui::SameLine();
        if (ImGui::Button("Reset"))
        {
            CPU::GetInstance()->Reset();
        }
        ImGui::Separator();

        ImGui::BeginChild("child");
        ImGui::Columns(2);

        //https://github.com/ocornut/imgui/issues/124
        int displayStart = 0;
        int displayEnd = Chip8::MEMORY_SIZE;
        float textHeight = ImGui::GetTextLineHeight();
        ImGui::CalcListClipping(Chip8::MEMORY_SIZE, textHeight, &displayStart, &displayEnd);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + displayStart * textHeight);

        std::array<std::uint8_t, Chip8::MEMORY_SIZE> memory = CPU::GetInstance()->GetMemory();
        for (size_t i = displayStart; i < displayEnd; i++)
        {
            ImGui::Text("0x%X", i);
            ImGui::NextColumn();

            ImGui::Text("0x%X", memory[i]);
            ImGui::NextColumn();
        }
        
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + (Chip8::MEMORY_SIZE - displayEnd) * textHeight);
        ImGui::EndChild();
    }
    
    ImGui::End();
}