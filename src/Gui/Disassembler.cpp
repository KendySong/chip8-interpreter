#include "Disassembler.hpp"

Disassembler::Disassembler()
{
    _renderAtPC = false;
}

void Disassembler::HandleInterface()
{
    if (ImGui::Begin("Disassembler"))
    {
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

    case 0x2000 :
        ImGui::Text("CALL 0x%X", opCode & 0x0FFF);
        break;

    case 0x3000 :
        ImGui::Text("SE V[%X], %X", (opCode & 0x0F00) >> 8, opCode & 0x00FF);
        break;

    case 0x4000 :
        ImGui::Text("SNE V[%X], %X", (opCode & 0x0F00) >> 8, opCode & 0x00FF);
        break;

    case 0x5000 :
        ImGui::Text("SE V[%X], V[%X]", (opCode & 0x0F00) >> 8, (opCode & 0x00F0) >> 4);
        break;

    case 0x6000 :
        ImGui::Text("LD V[%X], %X", (opCode & 0x0F00) >> 8, opCode & 0x00FF);
        break;

    case 0x7000 :
        ImGui::Text("ADD V[%X], %X", (opCode & 0x0F00) >> 8, opCode & 0x00FF);
        break;

    case 0x8000 :
        switch (opCode & 0x000F)
        {
            case 0x0000 :
                ImGui::Text("LD V[%X], V[%X]", (opCode & 0x0F00) >> 8, (opCode & 0x00F0) >> 4);
                break;

            case 0x0001 :
                ImGui::Text("OR V[%X], V[%X]", (opCode & 0x0F00) >> 8, (opCode & 0x00F0) >> 4);
                break;

            case 0x0002 :
                ImGui::Text("AND V[%X], V[%X]", (opCode & 0x0F00) >> 8, (opCode & 0x00F0) >> 4);
                break;

            case 0x0003 :
                ImGui::Text("XOR V[%X], V[%X]", (opCode & 0x0F00) >> 8, (opCode & 0x00F0) >> 4);
                break;

            case 0x0004 :   
                ImGui::Text("ADD V[%X], V[%X]", (opCode & 0x0F00) >> 8, (opCode & 0x00F0) >> 4);
                break;

            case 0x0005 :
                ImGui::Text("SUB V[%X], V[%X]", (opCode & 0x0F00) >> 8, (opCode & 0x00F0) >> 4);
                break;

            case 0x0006 :
                ImGui::Text("SHR V[%X]", (opCode & 0x0F00) >> 8);
                break;

            case 0x0007 :
                ImGui::Text("SUBN V[%X], V[%X]", (opCode & 0x0F00) >> 8, (opCode & 0x00F0) >> 4);
                break;

            case 0x000E :
                ImGui::Text("SHL V[%X]", (opCode & 0x0F00) >> 8);
                break;
        }
        break;

    case 0x9000 :
        ImGui::Text("SNE V[%X], V[%X]", (opCode & 0x0F00) >> 8, (opCode & 0x00F0) >> 4);
        break;

    case 0xA000 :
        ImGui::Text("LD I, %X", opCode & 0x0FFF);
        break;

    case 0xB000 :
        ImGui::Text("JP V[0], %X", opCode & 0x0FFF);
        break;

    case 0xC000 :
        ImGui::Text("RND V[%X], %X", (opCode & 0x0F00) >> 8, opCode & 0x0FF);
        break;

    case 0xD000 :
        ImGui::Text("DRW V[%X], V[%X], %X", (opCode & 0x0F00) >> 8, (opCode & 0x00F0) >> 4, opCode & 0x000F);
        break;

    case 0xE000 :
        switch (opCode & 0x000F)
        {
        case 0x000E:
            ImGui::Text("SKP V[%X]", (opCode & 0x0F00) >> 8);
            break;

        case 0x0001:
            ImGui::Text("SKNP V[%X]", (opCode & 0x0F00) >> 8);
            break;
        }
        break;
        
    case 0xF000 :
        switch (opCode & 0x00FF)
        {
            case 0x007 :
                ImGui::Text("LD V[%X], DT", (opCode & 0x0F00) >> 8);
                break;
            
            case 0x000A :
                ImGui::Text("LD V[%X], K", (opCode & 0x0F00) >> 8);
                break;

            case 0x0015 :
                ImGui::Text("LD DT, V[%X]", (opCode & 0x0F00) >> 8);
                break;

            case 0x0018 :
                ImGui::Text("LD ST, V[%X]", (opCode & 0x0F00) >> 8);
                break;

            case 0x001E :
                ImGui::Text("ADD I, V[%X]", (opCode & 0x0F00) >> 8);
                break;

            case 0x0029 :
                ImGui::Text("ADD F, V[%X]", (opCode & 0x0F00) >> 8);
                break;

            case 0x0033 :
                ImGui::Text("ADD B, V[%X]", (opCode & 0x0F00) >> 8);    
                break;

            case 0x055 :
                ImGui::Text("LD [%X], V[%X]", CPU::GetInstance()->GetIndex(), (opCode & 0x0F00) >> 8);
                break;

            case 0x0065 :
                ImGui::Text("LD V[%X], [%X]",  (opCode & 0x0F00) >> 8, CPU::GetInstance()->GetIndex());
                break;
        }
        break;
    }

    

}