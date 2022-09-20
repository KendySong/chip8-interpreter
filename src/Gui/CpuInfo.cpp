#include "CpuInfo.hpp"

void CpuInfo::HandleInterface()
{
    ImGui::Begin("CPU");
    ImGui::Text("PC : %x", CPU::GetInstance()->GetProgramCounter());
    ImGui::Text("I  : %x", CPU::GetInstance()->GetIndex());
    ImGui::Separator();

    for (size_t i = 0; i < CPU::GetInstance()->GetRegister().size(); i++)
    {
        ImGui::Text("V[%x] %x", i, CPU::GetInstance()->GetRegister()[i]); 
    }    
    ImGui::End(); 
}