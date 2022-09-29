#pragma once

/**
 * @brief Program settings,
 * can be used everywhere.
 * Values are defined in Settings.cpp
 */
struct Settings
{
public :
    //window
    static unsigned int windowWidth;
    static unsigned int windowHeight;
    static const char* title;
    static float cpuSpeed;
};

/**
 * @brief Chip8 const values
 * 
 */
namespace Chip8
{
    static const unsigned int SCREEN_WIDTH = 64;
    static const unsigned int SCREEN_HEIGHT = 32;

    static const unsigned int REGISTER_SIZE = 16;
    static const unsigned int MEMORY_SIZE = 4096;

    static const unsigned int PROGRAM_START_LOC = 0x200;    //Program loading starting emplacement (load into _memory of cpu)
    static const unsigned int CHARACTER_START_LOC = 0x50;   //Character loading starting emplacement

    static const unsigned int MAX_SPRITE_WIDTH = 8;
    static const float TIMER_FREQUENCY = 60.0f;
};