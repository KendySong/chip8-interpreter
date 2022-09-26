#include "CpuInfo.hpp"

void CpuInfo::HandleInterface()
{
    ImGui::Begin("CPU");
    ImGui::Text("PC : %x", CPU::GetInstance()->GetProgramCounter());
    ImGui::Text("I  : %x", CPU::GetInstance()->GetIndex());
    ImGui::Separator();

    ImGui::Columns(2);
    for (int i = 0; i < CPU::GetInstance()->GetRegister().size(); i++)
    {
        ImGui::Text("V[%X] %X", i, CPU::GetInstance()->GetRegister()[i]);
        ImGui::NextColumn();
    }

    ImGui::End(); 
}