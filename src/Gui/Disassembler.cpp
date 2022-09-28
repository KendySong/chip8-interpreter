#include "Disassembler.hpp"

Disassembler::Disassembler()
{
    _renderAtPC = false;
}

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
            MemoryViewer::GetInstance()->GetMemoryRom().clear();
        }
        ImGui::SameLine();
        ImGui::Checkbox("Scroll to PC", &_renderAtPC);     
        ImGui::Separator();

        ImGui::BeginChild("child");
        ImGui::Columns(2);

        ImGui::TextUnformatted("Address");
        ImGui::NextColumn();
        ImGui::TextUnformatted("Value");
        ImGui::NextColumn();

        //https://github.com/ocornut/imgui/issues/124      
        int displayStart = 0;
        int displayEnd = Chip8::MEMORY_SIZE;
        float textHeight = ImGui::GetTextLineHeight();
        ImGui::CalcListClipping(Chip8::MEMORY_SIZE, textHeight, &displayStart, &displayEnd);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + displayStart * textHeight);

        static float lineHeight = ImGui::GetTextLineHeight();
        std::uint16_t pc = CPU::GetInstance()->GetProgramCounter();
        std::array<std::uint8_t, Chip8::MEMORY_SIZE> memory = CPU::GetInstance()->GetMemory();
        for (size_t i = displayStart; i < displayEnd; i++)
        {
            char address[6];
            snprintf(address, sizeof(address), "0x%X", i);        
            ImGui::Selectable(address, i == pc);
            ImGui::NextColumn();


            ImGui::Text("0x%X", memory[i]);
            ImGui::NextColumn();
        }

        if (_renderAtPC)
        {
            ImGui::SetScrollY(pc * lineHeight);
        }   
               
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + (Chip8::MEMORY_SIZE - displayEnd) * textHeight);
        ImGui::EndChild();
    }
    
    ImGui::End();
}