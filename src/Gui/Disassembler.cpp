#include "Disassembler.hpp"

void Disassembler::HandleInterface()
{
    ImGui::Begin("Disassembler");
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
        char memoryEmplacement[6];
        snprintf(memoryEmplacement, sizeof(memoryEmplacement), "0x%X", i);
        ImGui::Text(memoryEmplacement);

        ImGui::NextColumn();

        char instruction[6];
        snprintf(instruction, sizeof(instruction), "0x%X", memory[i]);
        ImGui::Text(instruction);

        ImGui::NextColumn();
    }
    
    ImGui::EndChild();
    ImGui::End();
}