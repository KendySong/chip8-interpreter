#include "CPU.hpp"

CPU* CPU::_cpu = nullptr;
CPU::CPU()
{
    Reset();
}

CPU* CPU::GetInstance()
{
    if (_cpu == nullptr)
    {
        _cpu = new CPU();
    }
    return _cpu;
}

void CPU::Update()
{   
    if (_isRunning && _programCounter < Chip8::MEMORY_SIZE)
    {
        //Assemble 2 byte for getting raw op code
        std::uint16_t opCode =  _memory[_programCounter];
        opCode <<= 8;
        opCode |= _memory[_programCounter + 1];
        _programCounter += 2;
    
        //Decode the instruction and execute him
        switch (opCode & 0xF000)
        {
        case 0x0000 :
            switch (opCode & 0x000F)
            {
            case 0x0000 :
                ClearScreen(); //cls
                break;
            
            case 0x000E : 
                //ret
                break;
            
            default:
                //=> sys addr
                break;
            }
            break;




        //Jump
        case 0x1000 :
            _programCounter = opCode & 0x0FFF;
            break;

        default :           
            std::string log = "[ERROR] instruction 0x" + std::to_string(opCode) + " not recognize\n";
            ConsoleLog::GetInstance()->AddLog(log.c_str());
            break;
        }
    }
    else if (_isRunning && _programCounter >= Chip8::MEMORY_SIZE)
    {
        _isRunning = false;
        ConsoleLog::GetInstance()->AddLog("[INFO] program execution finished\n");
    }
}

void CPU::Run() noexcept
{
    _isRunning = true;
}

void CPU::Pause() noexcept
{
    _isRunning = false;
}

void CPU::Reset() noexcept
{
    _isRunning = false;
    _programCounter = Chip8::PROGRAM_START_LOC;

    memset(&_register, 0, sizeof(_register));
    memset(&_memory, 0, sizeof(_memory));
    ClearScreen();
    
    std::uint8_t characters[]
    {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    //Load font into memory (the main program is loaded from menu.cpp)
    for (size_t i = 0; i < sizeof(characters) / sizeof(std::uint8_t); i++)
    {
        _memory[Chip8::CHARACTER_START_LOC + i] = characters[i];
    }
}

void CPU::ClearScreen() noexcept
{
    for (size_t i = 0; i < _pixelRender.size(); i++)
    {
        std::fill(_pixelRender[i].begin(), _pixelRender[i].end(), false);
    }
}

std::array<std::uint8_t, Chip8::MEMORY_SIZE>& CPU::GetMemory() noexcept
{
    return _memory;
}

std::array<std::uint8_t, Chip8::REGISTER_SIZE>& CPU::GetRegister() noexcept
{
    return _register;
}

std::array<std::array<bool, Chip8::SCREEN_WIDTH>, Chip8::SCREEN_HEIGHT>& CPU::GetPixelRender() noexcept
{
    return _pixelRender;
}