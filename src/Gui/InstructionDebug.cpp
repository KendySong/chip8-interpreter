#include "InstructionDebug.hpp"

void InstructionDebug::HandleInterface()
{
    ImGui::Begin("Instruction");
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
    ImGui::End();
}