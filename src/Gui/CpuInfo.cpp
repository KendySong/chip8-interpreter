#include "CpuInfo.hpp"

void CpuInfo::HandleInterface()
{
    if (ImGui::Begin("CPU"))
    {
        ImGui::Text("PC : %X", CPU::GetInstance()->GetProgramCounter());
        ImGui::Text("I  : %X", CPU::GetInstance()->GetIndex());
        ImGui::Separator();

        ImGui::Columns(2);
        for (int i = 0; i < CPU::GetInstance()->GetRegister().size(); i++)
        {
            ImGui::Text("V[%X] %X", i, CPU::GetInstance()->GetRegister()[i]);
            ImGui::NextColumn();
        }
    }
    
    ImGui::End(); 
}