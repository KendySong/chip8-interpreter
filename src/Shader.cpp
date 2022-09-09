#include "Shader.hpp"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
    const char* vertexShaderSource = "";
    const char* fragmentShaderSource = "";

    std::ifstream fileReader(vertexShaderPath);
    if (fileReader.is_open())
    {
        std::stringstream fileStream;
        fileStream << fileReader.rdbuf();

        std::string fileString = fileStream.str();
        vertexShaderSource = fileString.c_str();
    }
    else
    {
        std::cout << "[ERROR] vertex shader not found\n";
    }
    
    fileReader.close();
    
    fileReader.open(fragmentShaderPath);
    if (fileReader.is_open())
    {
        std::stringstream fileStream;
        fileStream << fileReader.rdbuf();

        std::string fileString = fileStream.str();
        fragmentShaderSource = fileString.c_str();
    }
    else
    {
        std::cout << "[ERROR] fragment shader not found\n";
    }

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    int vertexCompileStatus = 0;
    int fragmentCompileStatus = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexCompileStatus);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentCompileStatus);

    char compileErrorMessage[512];
    if (!vertexCompileStatus)
    {
        glGetShaderInfoLog(vertexShader, sizeof(compileErrorMessage), NULL, compileErrorMessage);
        std::cout << "[ERROR] vertex shader compile error" << "\n";
        std::cout << compileErrorMessage << "\n";
    }

    if (!fragmentCompileStatus)
    {
        glGetShaderInfoLog(vertexShader, sizeof(compileErrorMessage), NULL, compileErrorMessage);
        std::cout << "[ERROR] fragment shader compile error" << "\n";
        std::cout << compileErrorMessage << "\n";
    }

    _shaderProgram = glCreateProgram();
    glAttachShader(_shaderProgram, vertexShader);
    glAttachShader(_shaderProgram, fragmentShader);
    glLinkProgram(_shaderProgram);
    glDetachShader(_shaderProgram, vertexShader);
    glDetachShader(_shaderProgram, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glUseProgram(_shaderProgram);
}

unsigned int Shader::GetShaderProgram()
{
    return _shaderProgram;
}