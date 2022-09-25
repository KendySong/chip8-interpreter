#include <string>
#include <array>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ConsoleLog.hpp"

#include "../Render/Shader.hpp"

#include "../Chip8/CPU.hpp"

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
    void Init(unsigned int shaderID);

    /**
     * @brief Render chip8 screen output
     * 
     */
    void HandleInterface(); 

    /**
     * @brief Generate grid of pixels
     * 
     */
    void InitializeScreen();

private :
    glm::vec2 _pixelSize;
    ImVec2 _reducedRatio;
    unsigned int _positionUniform;
    unsigned int _fbRender;
    unsigned int _textureRender;
};