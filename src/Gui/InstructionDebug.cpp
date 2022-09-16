#include "InstructionDebug.hpp"

void InstructionDebug::HandleInterface()
{
    ImGui::Begin("Instruction");
    ImGui::Button("Start");
    ImGui::SameLine();
    ImGui::Button("Step by step");
    ImGui::SameLine();
    ImGui::Button("Stop");
    ImGui::SameLine();
    ImGui::Button("Restart");
    ImGui::Separator();
    ImGui::End();
}