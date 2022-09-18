#include "CPU.hpp"

CPU* CPU::_cpu = nullptr;
CPU::CPU()
{
    _isRunning = false;
    _programCounter = PROGRAM_START_LOC;

    memset(&_register, 0, sizeof(_register));
    memset(&_memory, 0, sizeof(_memory));
    
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
        _memory[CHARACTER_START_LOC + i] = characters[i];
    }
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
    if (_isRunning)
    {
        //Assemble 2 byte for getting raw op code
        std::uint16_t opCode =  _memory[_programCounter];
        opCode <<= 8;
        opCode |= _memory[_programCounter + 1];
        _programCounter += 2;
     
        std::uint16_t instruction = opCode & 0xF000;
        switch (instruction)
        {
        case 0x1000 :
            _programCounter = opCode & 0x0FFF;
            std::cout << _programCounter << "\n";
            break;

        default :
            std::string log = "[ERROR] instruction 0x" + std::to_string(instruction) + " not recognize\n";
            ConsoleLog::GetInstance()->AddLog(log.c_str());
            break;
        }
        

        if (_programCounter >= MEMORY_SIZE)
        {
            _isRunning = false;
            ConsoleLog::GetInstance()->AddLog("[INFO] program execution finished\n");
        }
    }
}

std::array<std::uint8_t, MEMORY_SIZE>& CPU::GetMemory() noexcept
{
    return _memory;
}

std::array<std::uint8_t, REGISTER_SIZE>& CPU::GetRegister() noexcept
{
    return _register;
}

void CPU::Run() noexcept
{
    _isRunning = true;
}

void CPU::Pause() noexcept
{
    _isRunning = false;
}