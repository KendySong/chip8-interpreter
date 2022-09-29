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
        ImGui::Columns(3);

        ImGui::TextUnformatted("Address");
        ImGui::NextColumn();
        ImGui::TextUnformatted("Value");
        ImGui::NextColumn();
        ImGui::TextUnformatted("Instruction");
        ImGui::NextColumn();

        //https://github.com/ocornut/imgui/issues/124      
        int displayStart = 0;
        int displayEnd = Chip8::MEMORY_SIZE;
        float textHeight = ImGui::GetTextLineHeight();
        ImGui::CalcListClipping(Chip8::MEMORY_SIZE, textHeight, &displayStart, &displayEnd);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + displayStart * textHeight);

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

            if (i % 2 == 0)
            {
                DisassembleInstruction((memory[i] << 8) | memory[i + 1]);
            }
            else
            {
                ImGui::TextUnformatted("");
            }

            ImGui::NextColumn();
        }

        if (_renderAtPC)
        {
            ImGui::SetScrollY(pc * textHeight);
        }   
               
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + (Chip8::MEMORY_SIZE - displayEnd) * textHeight);
        ImGui::EndChild();     
    }
    
    ImGui::End();
}

void Disassembler::DisassembleInstruction(std::uint16_t opCode)
{
    switch (opCode & 0xF000)
    {
    case 0x0000 :
        switch (opCode & 0x00FF)
        {
        case 0x00E0 :
            ImGui::TextUnformatted("CLS");
            break;
        
        case 0x00EE :
            ImGui::TextUnformatted("RET");
            break;
        }
        break;
    
    case 0x1000 :       
        ImGui::Text("JP 0x%X", opCode & 0x0FFF);
        break;

    case 0x6000 :
        ImGui::Text("LD V[%X], %X", (opCode & 0x0F00) >> 8, opCode & 0x00FF);
        break;

    case 0x7000 :
        ImGui::Text("ADD V[%X], %X", (opCode & 0x0F00) >> 8, opCode & 0x00FF);
        break;

    case 0xA000 :
        ImGui::Text("LD I, %X", opCode & 0x0FFF);
        break;

    case 0xD000 :
        ImGui::Text("DRW V[%X], V[%X], %X", (opCode & 0x0F00) >> 8, (opCode & 0x00F0) >> 4, opCode & 0x000F);
        break;
    }

}