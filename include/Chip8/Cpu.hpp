#include <cstring>
#include <array>

#include <iostream>

#include "Settings.hpp"

#pragma once
class CPU
{
public :
    CPU();

    static CPU* GetInstance();

    void Update();

    std::array<std::uint8_t, REGISTER_SIZE>& GetRegister() noexcept;

    std::array<std::uint8_t, MEMORY_SIZE>& GetMemory() noexcept;

    void Run() noexcept;

    void Pause() noexcept;

private :
    static CPU* _cpu;

    bool _isRunning;
    std::uint16_t _programCounter;
    std::uint16_t _index;

    std::array<std::uint8_t, REGISTER_SIZE> _register;
    std::array<std::uint8_t, MEMORY_SIZE> _memory;    
};