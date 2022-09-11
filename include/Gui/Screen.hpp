#include <glad/glad.h>

#include "Gui.hpp"
#include "Settings.hpp"

#pragma once
class Screen : public Gui
{
public :
    Screen() = default;

    void Init();

    void HandleInterface(); 

private :
    ImVec2 _reducedRatio;
    unsigned int _fbRender;
    unsigned int _textureRender;
};