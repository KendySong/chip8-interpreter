#include <iostream>
#include <sstream>
#include <fstream>

#include <glad/glad.h>

#pragma once 
class Shader
{
private :
    unsigned int _shaderProgram;

public :
    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

    unsigned int GetShaderProgram();
};