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
    if (_programCounter < Chip8::MEMORY_SIZE)
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
                _sp--;
                _programCounter = _stack[_sp];
                break;
            
            default:
                LogUnknownInstruction(opCode);
                break;
            }
            break;

        //JMP addr
        case 0x1000 :
            _programCounter = (opCode & 0x0FFF);
            break;

        //CALL addr
        case 0x2000 :
            _stack[_sp] = _programCounter;
            _sp++;
            _programCounter = (opCode & 0x0FFF);
            break;

        //SE Vx, byte
        case 0x3000 :
            if (_register[(opCode & 0x0F00) >> 8] == (opCode & 0x00FF))
            {
                _programCounter += 2;
            }
            break;

        //SNE Vx, byte
        case 0x4000 :
            if (_register[(opCode & 0x0F00) >> 8] != (opCode & 0x00FF))
            {
                _programCounter += 2;
            }
            break;

        //SE Vx, Vy
        case 0x5000 :
            if (_register[(opCode & 0x0F00) >> 8] == _register[(opCode & 0x00F0) >> 4])
            {
                _programCounter += 2;
            }
            break; 

        //Set register X to NN
        case 0x6000 :
            _register[(opCode & 0x0F00) >> 8] = (opCode & 0x00FF);
            break;

        //Add NN to register X
        case 0x7000 :
            _register[(opCode & 0x0F00) >> 8] += (opCode & 0x00FF);
            break;

        case 0x8000 :
            switch (opCode & 0x000F)
            {
            //LD Vx, Vy
            case 0x0000 :
                _register[(opCode & 0x0F00) >> 8] = _register[(opCode & 0x00F0) >> 4];
                break;

            //OR Vx, Vy
            case 0x0001 :
                _register[(opCode & 0x0F00) >> 8] |= _register[(opCode & 0x00F0) >> 4];
                break;

            //AND Vx, Vy
            case 0x0002 :
                _register[(opCode & 0x0F00) >> 8] &= _register[(opCode & 0x00F0) >> 4];
                break;

            //XOR Vx, Vy
            case 0x0003 :
                _register[(opCode & 0x0F00) >> 8] ^= _register[(opCode & 0x00F0) >> 4];
                break;

            //ADD Vx, Vy
            case 0x0004 :   
                _x = (opCode & 0x0F00) >> 8;
                _y = (opCode & 0x00F0) >> 4;          
                _register[Chip8::REGISTER_SIZE - 1] = _register[_x] + _register[_y] > 255 ? 1 : 0;
                _register[_x] = ((_register[_x] + _register[_y]) & 0x00FF);
                break;

            //SUB Vx, Vy
            case 0x0005 :
                _x = (opCode & 0x0F00) >> 8;
                _y = (opCode & 0x00F0) >> 4;
                _register[Chip8::REGISTER_SIZE - 1] = _register[_x] > _register[_y] ? 1 : 0;
                _register[_x] -=_register[_y];  
                break;

            //SHR Vx {, Vy}
            case 0x0006 :
                _x = (opCode & 0x0F00) >> 8;
                _register[Chip8::REGISTER_SIZE - 1] = _register[_x] & 0x0001;
                _register[_x] >>= 1;
                break;

            //SUBN Vx, Vy
            case 0x0007 :
                _x = (opCode & 0x0F00) >> 8;
                _y = (opCode & 0x00F0) >> 4;      
                _register[Chip8::REGISTER_SIZE - 1] = _register[_y] > _register[_x] ? 1 : 0;
                _register[_x] = _register[_y] - _register[_x];
                break;

            //SHL Vx {, Vy}
            case 0x000E :
                _x = (opCode & 0x0F00) >> 8;
                _y = (opCode & 0x00F0) >> 4;
                _register[Chip8::REGISTER_SIZE - 1] = ((_register[_x] >> 7) & 0x0001);          
                _register[_x] <<= 1;
                break;
            
            default:
                LogUnknownInstruction(opCode);
                break;
            }
            break;
        
        //SNE Vx, Vy
        case 0x9000 :
            if (_register[(opCode & 0x0F00) >> 8] != _register[(opCode & 0x00F0) >> 4])
            {
                _programCounter += 2;
            }        
            break;

        //Set I to NNN
        case 0xA000 :
            _index = (opCode & 0x0FFF);
            break;
            
        //JP V0, addr
        case 0xB000 :
            _programCounter = (opCode & 0x0FFF) + _register[0];
            break;

        //RND Vx, byte
        case 0xC000 :
            _register[(opCode & 0x0F00) >> 8] = (rand() % 256) & (opCode & 0x00FF);
            break;

        //DRW Vx, Vy, nibble
        case 0xD000 :
            DrawSprite(opCode);
            break;

        case 0xE000 :
            switch (opCode & 0x000F)
            {
            //SKP Vx
            case 0x000E:
                if (_register[(opCode & 0x0F00) >> 8] == _keyMap.at(_currentKeyDown) && (_actionKey == 1 || _actionKey == 2))
                {
                    _programCounter += 2;
                }            
                break;

            //SKNP Vx
            case 0x0001:
                if (_register[(opCode & 0x0F00) >> 8] != _keyMap.at(_currentKeyDown))
                {
                    _programCounter += 2;
                }
                break;
            
            default:
                LogUnknownInstruction(opCode);
                break;
            }
            break;

        case 0xF000 :
            switch (opCode & 0x00FF)
            {
            //LD Vx, DT
            case 0x007 :
                _register[(opCode & 0x0F00) >> 8] = _delay;
                break;
            
            //LD Vx, K
            case 0x000A :
                if (_actionKey == 0)
                {
                    _programCounter -= 2;
                }
                else if (_keyMap.find(_currentKeyDown) != _keyMap.end())
                {
                    _register[(opCode & 0x0F00) >> 8] = _keyMap.at(_currentKeyDown);
                }
                break;

            //LD DT, Vx
            case 0x0015 :
                _delay = _register[(opCode & 0x0F00) >> 8];
                break;

            //LD ST, Vx
            case 0x0018 :
                _sound = _register[(opCode & 0x0F00) >> 8];
                break;

            //ADD I, Vx
            case 0x001E :
                _index += _register[(opCode & 0x0F00) >> 8];
                break;

            //LD F, Vx
            case 0x0029 :
                _index = Chip8::CHARACTER_START_LOC + _register[(opCode & 0x0F00) >> 8] * 5;
                break;

            //LD B, Vx
            case 0x0033 :       
                StoreBCD(opCode);
                break;

            //LD [I], Vx
            case 0x055 :
                for (size_t i = 0; i <= (opCode & 0x0F00); i++)
                {
                    _memory[_index + i] = _register[i];
                }                   
                break;

            //LD Vx, [I]
            case 0x0065 :
                for (size_t i = 0; i <= (opCode & 0x0F00); i++)
                {
                    _register[_index + i] = _register[i];
                }
                break;

            default:
                LogUnknownInstruction(opCode);
                break;
            }
            break;

        default :           
            LogUnknownInstruction(opCode);
            break;
        }
    }
    else if (_programCounter >= Chip8::MEMORY_SIZE)
    {
        _isRunning = false;
        ConsoleLog::GetInstance()->AddLog("[INFO] program execution finished\n");
    }
}

void CPU::DrawSprite(std::uint16_t opCode)
{
    /*
    We get first x and y position in the screen
    and we start draw sprite at this position.

    We set on or off each pixel depending the
    status of pixel and the current using bit
    of the sprite.

    Exemple of '2' sprite
    ****    11110000
       *    00010000
    ****    11110000
    *       10000000
    ****    11110000
    */

    std::uint8_t xScreen = _register[(opCode & 0x0F00) >> 8] % Chip8::SCREEN_WIDTH;
    std::uint8_t yScreen = _register[(opCode & 0x00F0) >> 4] % Chip8::SCREEN_HEIGHT;

    _register[Chip8::REGISTER_SIZE - 1] = 0;
    
    std::uint16_t height = opCode & 0x000F;
    for (size_t y = 0; y < height; y++)
    {
        std::uint8_t spriteByte = _memory[_index + y]; //=> 11110000

        //Draw sprite line
        for (size_t x = 0; x < Chip8::MAX_SPRITE_WIDTH; x++)
        {       
            if (xScreen + x < Chip8::SCREEN_WIDTH && yScreen + y < Chip8::SCREEN_HEIGHT)
            {
                //Get sprite pixel with AND mask and x position
                std::uint8_t spritePixel = spriteByte & (0x80 >> x);

                //Set on or off pixel
                if (!_pixelRender[yScreen + y][xScreen + x] && spritePixel != 0)
                {
                    _pixelRender[yScreen + y][xScreen + x] = true;
                }
                else if (_pixelRender[yScreen + y][xScreen + x] && spritePixel != 0)
                {
                    _pixelRender[yScreen + y][xScreen + x] = false;
                    _register[Chip8::REGISTER_SIZE - 1] = 1;
                }
            }
            else
            {
                break;
            }  
        }  
    }
}

void CPU::StoreBCD(std::uint8_t opCode)
{
    std::uint8_t vx = _register[(opCode & 0x0F00) >> 8];         
    _memory[_index + 2] = vx % 10;
    vx /= 10;

    _memory[_index + 1] = vx % 10;
    vx /= 10;

    _memory[_index] = vx;
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
    srand(time(nullptr));

    _isRunning = false;
    _currentKeyDown = 0;
    _actionKey = 0;
    _index = 0;
    _sp = 0;
    _programCounter = Chip8::PROGRAM_START_LOC;

    memset(&_register, 0, sizeof(_register));
    memset(&_memory, 0, sizeof(_memory));
    memset(&_stack, 0, sizeof(_stack));
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
  
     /*
    //Translate keyboard inputs
    _keyMap[glfwGetKeyScancode(GLFW_KEY_1)] = 1;
    _keyMap[glfwGetKeyScancode(GLFW_KEY_2)] = 2;
    _keyMap[glfwGetKeyScancode(GLFW_KEY_3)] = 3;
    _keyMap[glfwGetKeyScancode(GLFW_KEY_4)] = 0xC;

    _keyMap[glfwGetKeyScancode(GLFW_KEY_Q)] = 4;
    _keyMap[glfwGetKeyScancode(GLFW_KEY_W)] = 5;
    _keyMap[glfwGetKeyScancode(GLFW_KEY_E)] = 6;
    _keyMap[glfwGetKeyScancode(GLFW_KEY_R)] = 0xD;

    _keyMap[glfwGetKeyScancode(GLFW_KEY_A)] = 7;
    _keyMap[glfwGetKeyScancode(GLFW_KEY_S)] = 8;
    _keyMap[glfwGetKeyScancode(GLFW_KEY_D)] = 9;
    _keyMap[glfwGetKeyScancode(GLFW_KEY_F)] = 0xE;

    _keyMap[glfwGetKeyScancode(GLFW_KEY_Z)] = 0xA;
    _keyMap[glfwGetKeyScancode(GLFW_KEY_X)] = 0;
    _keyMap[glfwGetKeyScancode(GLFW_KEY_C)] = 0xB;
    _keyMap[glfwGetKeyScancode(GLFW_KEY_V)] = 0xF;
    */
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

void CPU::SetKeyInput(int scanCode, int action)
{
    _currentKeyDown = scanCode;
    _actionKey = action;
}

bool CPU::GetIsRunning() noexcept
{
    return _isRunning;
}

std::uint16_t CPU::GetIndex() noexcept
{
    return _index;
}

std::uint16_t CPU::GetProgramCounter() noexcept
{
    return _programCounter;
}

std::uint8_t& CPU::GetSP() noexcept
{
    return _sp;
}

std::array<std::uint8_t, Chip8::REGISTER_SIZE>& CPU::GetRegister() noexcept
{
    return _register;
}

std::uint8_t CPU::GetDelay() noexcept
{
    return _delay;
}

void CPU::SetDelay(std::uint8_t delay) noexcept
{
    _delay = delay;
}

std::uint8_t CPU::GetSound() noexcept
{
    return _sound;
}

void CPU::SetSound(std::uint8_t sound) noexcept
{
    _sound = sound;
}

std::array<std::uint16_t, Chip8::REGISTER_SIZE>& CPU::GetStack() noexcept
{
    return _stack;
}

std::array<std::uint8_t, Chip8::MEMORY_SIZE>& CPU::GetMemory() noexcept
{
    return _memory;
}

std::array<std::array<bool, Chip8::SCREEN_WIDTH>, Chip8::SCREEN_HEIGHT>& CPU::GetPixelRender() noexcept
{
    return _pixelRender;
}