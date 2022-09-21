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
            //CLS
            case 0x0000 :
                ClearScreen();
                break;
            
            //RTS
            case 0x000E : 
                _programCounter = _stack.top();
                break;
            
            default:
                LogUnknownInstruction(opCode);
                break;
            }
            break;

        //JMP
        case 0x1000 :
            _programCounter = opCode & 0x0FFF;
            break;

        //CALL
        case 0x2000 :
            _stack.push(_programCounter);
            _programCounter = opCode & 0x0FFF;
            break;

        //Set register X to NN
        case 0x6000 :
            _register[opCode & 0x0F00] = opCode & 0x00FF;
            break;

        //Add NN to register X
        case 0x7000 :
            _register[opCode & 0x0F00] += opCode & 0x00FF;
            break;

        //Set I to NNN
        case 0xA000 :
            _index = opCode & 0x0FFF;
            break;

        //Draw sprite
        case 0xD000 :
            DrawSprite(opCode);
            break;

        default :           
            LogUnknownInstruction(opCode);
            break;
        }
    }
    else if (_isRunning && _programCounter >= Chip8::MEMORY_SIZE)
    {
        _isRunning = false;
        ConsoleLog::GetInstance()->AddLog("[INFO] program execution finished\n");
    }
}

void CPU::DrawSprite(std::uint16_t opCode)
{
    std::uint8_t xScreen = _register[(opCode & 0x0F00) >> 8] % Chip8::SCREEN_WIDTH;
    std::uint8_t yScreen = _register[(opCode & 0x00F0) >> 4] % Chip8::SCREEN_HEIGHT;
    _register[_register.size() - 1] = 0;

    std::uint16_t height = opCode & 0x000F;
    for (size_t y = 0; y < height; y++)
    {
        std::uint8_t spriteByte = _memory[_index + y];
        for (size_t x = 0; x < Chip8::MAX_SPRITE_WIDTH; x++)
        {
            if (xScreen + x < Chip8::SCREEN_WIDTH)
            {
                if ((spriteByte >> Chip8::MAX_SPRITE_WIDTH - x - 1) != 0 && _pixelRender[yScreen + y][xScreen + x])
                {
                    _pixelRender[yScreen + y][xScreen + x] = false;
                    _register[_register.size() - 1] = 1;
                }
                else if (!_pixelRender[yScreen + y][xScreen + x] && (spriteByte >> Chip8::MAX_SPRITE_WIDTH - x - 1))
                {
                    _pixelRender[yScreen + y][xScreen + x] = true;
                }
            }         
        }  
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
    _index = 0;
    _programCounter = Chip8::PROGRAM_START_LOC;

    memset(&_register, 0, sizeof(_register));
    memset(&_memory, 0, sizeof(_memory));
    ClearScreen();
    
    std::array<std::uint8_t, 80> characters
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
    for (size_t i = 0; i < characters.size(); i++)
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

void CPU::LogUnknownInstruction(std::uint16_t opCode) noexcept
{
    char errorMessage[42];
    snprintf(errorMessage, sizeof(errorMessage), "[ERROR] instruction 0x%X not recognize\n", opCode);
    ConsoleLog::GetInstance()->AddLog(errorMessage);
}

std::uint16_t CPU::GetProgramCounter() noexcept
{
    return _programCounter;
}


std::uint16_t CPU::GetIndex() noexcept
{
    return _index;
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