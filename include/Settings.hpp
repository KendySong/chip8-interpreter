#pragma once

/**
 * @brief Program settings,
 * can be used everywhere
 */
struct Settings
{
public :
    //window
    static unsigned int windowWidth;
    static unsigned int windowHeight;
    static const char* title;

    //interface
    static unsigned int screenWidth;
    static unsigned int screenHeight;
    static unsigned int fpsTextSpace;
};

//chip8
static const unsigned int REGISTER_SIZE = 16;
static const unsigned int MEMORY_SIZE = 4096;

static const unsigned int PROGRAM_START_LOC = 0x200;    //Program loading starting emplacement (load into _memory of cpu)
static const unsigned int CHARACTER_START_LOC = 0x50;   //Character loading starting emplacement