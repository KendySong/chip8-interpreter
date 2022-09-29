#include "Debugger.hpp"

void Debugger::HandleInterface()
{
    ImGui::Begin("Debugger");
    ImGui::TextUnformatted("CPU speed (Instruction/ms)");
    ImGui::SameLine();
    ImGui::InputFloat(" ", &Settings::cpuSpeed);

    if (ImGui::Button("Run"))
    {
        CPU::GetInstance()->Run();
    }
    ImGui::SameLine();

    if (ImGui::Button("Next step"))
    {
        CPU::GetInstance()->Update();
    }
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

    ImGui::End();
}