#include "Disassembler.hpp"

Disassembler::Disassembler()
{
    for (size_t i = 0; i < CPU::GetInstance()->GetMemory().size(); i++)
    {
        char instructionAddress[6];
        snprintf(instructionAddress, sizeof(instructionAddress), "0x%X", i);
        _textBuffer.append(instructionAddress);
        _textBuffer.append("\n");
    }
}

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

    ImGui::Columns(3, "instruction disassembled");
    ImGui::TextUnformatted(_textBuffer.begin());
    for (size_t i = 0; i < CPU::GetInstance()->GetMemory().size(); i++)
    {
        //Display memory
    }
    
    
    ImGui::End();
}