#include <array>
#include <random>

#include "Settings.hpp"

#pragma once
class CPU
{
public :
    CPU();

    static CPU* GetInstance();

    std::array<std::uint8_t, MEMORY_SIZE>& GetMemory() noexcept;

private :
    static CPU* _cpu;

    std::array<std::uint8_t, REGISTER_SIZE> _register;
    std::uint16_t _pogramCounter;
    std::uint16_t _index;
    std::array<std::uint8_t, MEMORY_SIZE> _memory;
};