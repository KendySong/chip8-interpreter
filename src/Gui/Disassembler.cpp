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
        
        std::array<std::uint8_t, Chip8::MEMORY_SIZE> memory = CPU::GetInstance()->GetMemory();
        for (size_t i = 0; i < Chip8::MEMORY_SIZE; i++)
        {
            ImGui::Text("0x%X", i);

            ImGui::NextColumn();

            ImGui::Text("0x%X", memory[i]);

            ImGui::NextColumn();
        }
        
        ImGui::EndChild();
    }
    
    ImGui::End();
}