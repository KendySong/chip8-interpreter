#include <cstring>
#include <array>

#include "../Gui/ConsoleLog.hpp"

#include "Settings.hpp"

#pragma once
class CPU
{
public :
    CPU();

    static CPU* GetInstance();

    void Update();

    void Run() noexcept;

    void Pause() noexcept;

    std::array<std::uint8_t, Chip8::REGISTER_SIZE>& GetRegister() noexcept;

    std::array<std::uint8_t, Chip8::MEMORY_SIZE>& GetMemory() noexcept;

    std::array<std::array<bool, Chip8::SCREEN_WIDTH>, Chip8::SCREEN_HEIGHT>& GetPixelRender() noexcept;

private :
    static CPU* _cpu;

    bool _isRunning;
    std::uint16_t _programCounter;
    std::uint16_t _index;

    std::array<std::uint8_t, Chip8::REGISTER_SIZE> _register;
    std::array<std::uint8_t, Chip8::MEMORY_SIZE> _memory;    

    std::array<std::array<bool, Chip8::SCREEN_WIDTH>, Chip8::SCREEN_HEIGHT> _pixelRender;
};