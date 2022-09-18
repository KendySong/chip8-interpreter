#include <cstring>
#include <array>

#include "../Gui/ConsoleLog.hpp"

#include "Settings.hpp"

#pragma once
class CPU
{
public :
    /**
     * @brief Constructor
     * 
     */
    CPU();

    /**
     * @brief Get the instance of cpu
     * 
     * @return Pointer to the instance
     */
    static CPU* GetInstance();

    /**
     * @brief Read instructions, decode and execute them
     * 
     */
    void Update();

    /**
     * @brief Set on the cpu
     * 
     */
    void Run() noexcept;

    /**
     * @brief Stop the cpu instruction reading
     * 
     */
    void Pause() noexcept;

    /**
     * @brief Reset cpu and memory
     * 
     */
    void Reset() noexcept;

    /**
     * @brief Allow gui display cpu register values
     * 
     * @return std::array<std::uint8_t, Chip8::REGISTER_SIZE>& 
     */
    std::array<std::uint8_t, Chip8::REGISTER_SIZE>& GetRegister() noexcept;

    /**
     * @brief Allow menu.cpp load chip8 program into memory
     * 
     * @return Memory array
     */
    std::array<std::uint8_t, Chip8::MEMORY_SIZE>& GetMemory() noexcept;

    /**
     * @brief Get the Pixel Render object
     * 
     * @return 2D bool array for display or not a pixel
     */
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