#include <map>
#include <time.h>
#include <array>
#include <stack>
#include <algorithm>

#include <glfw/glfw3.h>

#include "Timer.hpp"

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
     * @brief Draw a sprite at the emplacement given in opCode
     * 
     * @param opCode decode and execute the instructions with settings
     */
    void DrawSprite(std::uint16_t opCode);

    /**
     * @brief Store BCD of VX into memory
     * 
     * @param opCode => instruction with parameters (Fx33 - LD B, Vx)
     */
    void StoreBCD(std::uint8_t opCode);

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
     * @brief Set false for each pixel drawing
     * 
     */
    void ClearScreen() noexcept;

    /**
     * @brief Log the unknown instruction
     * 
     * @param instruction to log into log window 
     */
    void LogUnknownInstruction(std::uint16_t opCode) noexcept;

     /**
     * @brief Set the Key Input object
     * 
     * @param scanCode => keyboard key emplacement
     * @param action => define if key is pressed, down or up
     */
    void SetKeyInput(int scanCode, int action);

    /**
     * @brief Get the cpu state
     * 
     * @return bool that represent cpu state
     */
    bool GetIsRunning() noexcept;

    /**
     * @brief Get the index reguister
     * 
     * @return index that point into memory
     */
    std::uint16_t GetIndex() noexcept;

    /**
     * @brief Get the pc that contain index of current 
     * executing instruction
     * 
     * @return pc that point into memory
     */
    std::uint16_t GetProgramCounter() noexcept;
    
    /**
     * @brief Getter of stack pointer
     * 
     * @return stack pointer reference
     */
    std::uint8_t& GetSP() noexcept;

    /**
     * @brief Allow gui display cpu register values
     * 
     * @return std::array<std::uint8_t, Chip8::REGISTER_SIZE>& 
     */
    std::array<std::uint8_t, Chip8::REGISTER_SIZE>& GetRegister() noexcept;

    /**
     * @brief Get the delay timer value
     * 
     * @return delay value
     */
    std::uint8_t GetDelay() noexcept;

    /**
     * @brief Set the delay timer value
     * 
     * @param new delay value
     */
    void SetDelay(std::uint8_t delay) noexcept;

    /**
     * @brief Get the sound timer value
     * 
     * @return sound value
     */
    std::uint8_t GetSound() noexcept;

    /**
     * @brief Set the sound timer value
     * 
     * @param new sound value
     */
    void SetSound(std::uint8_t sound) noexcept;

    /**
     * @brief Get the stack for display
     * 
     * @return Stack array
     */
    std::array<std::uint16_t, Chip8::REGISTER_SIZE>& GetStack() noexcept;

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
    std::uint16_t _index;
    std::uint16_t _programCounter;
    std::uint16_t _x;                                                                       //First register index getting from instruction
    std::uint16_t _y;                                                                       //Second register index getting from instruction                                                                
    std::array<std::uint8_t, Chip8::REGISTER_SIZE> _register;

    //Chip8 timer
    std::uint8_t _delay;
    std::uint8_t _sound;

    std::map<std::uint8_t, std::uint8_t> _keyMap;
    int _currentKeyDown;
    int _actionKey;

    std::uint8_t _sp;
    std::array<std::uint16_t, Chip8::REGISTER_SIZE> _stack;
    std::array<std::uint8_t, Chip8::MEMORY_SIZE> _memory;    
    std::array<std::array<bool, Chip8::SCREEN_WIDTH>, Chip8::SCREEN_HEIGHT> _pixelRender;   //2D array (each case represent if a case is on/off)
};