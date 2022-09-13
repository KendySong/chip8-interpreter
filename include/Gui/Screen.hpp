#include <glm/glm.hpp>
#include <glad/glad.h>

#include "Gui.hpp"
#include "Settings.hpp"

#pragma once

/**
 * @brief Render to output of chip8 code
 * 
 */
class Screen : public Gui
{
public :
    /**
     * @brief Constructor
     * 
     */
    Screen() = default;

    /**
     * @brief Create framebuffer for this component
     * and render into it
     */
    void Init();

    /**
     * @brief Render chip8 screen output
     * 
     */
    void HandleInterface(); 

private :
    void InitializeScreen();

    ImVec2 _reducedRatio;

    unsigned int _fbRender;
    unsigned int _textureRender;
};