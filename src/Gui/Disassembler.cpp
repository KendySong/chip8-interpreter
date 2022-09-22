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

    ImGui::EndChild();
    ImGui::End();
}