#include "Screen.hpp"

void Screen::Init(unsigned int shaderID)
{
    _positionUniform = glGetUniformLocation(shaderID, "position");

    _pixelSize = glm::vec2(2 / (float)Chip8::SCREEN_WIDTH, 2 / (float)Chip8::SCREEN_HEIGHT);
    unsigned int screenWidth = Settings::windowWidth / 1.5f;
    _reducedRatio = ImVec2(screenWidth, screenWidth / 2);

    glGenFramebuffers(1, &_fbRender);
    glBindFramebuffer(GL_FRAMEBUFFER, _fbRender);
    
    //Texture that is display on the sub window
    glGenTextures(1, &_textureRender);
    glBindTexture(GL_TEXTURE_2D, _textureRender);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Settings::windowWidth, Settings::windowHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glClearColor(0, 0, 0, 1);
}

void Screen::HandleInterface()
{
    glBindFramebuffer(GL_FRAMEBUFFER, _fbRender);
    glClear(GL_COLOR_BUFFER_BIT);

    for (float x = 0; x < Chip8::SCREEN_WIDTH; x++)
    {
        for (float y = 0; y < Chip8::SCREEN_HEIGHT; y++)
        {
            if (CPU::GetInstance()->GetPixelRender()[y][x])
            {
                glm::vec2 currentPosition(-1.0f + x  * _pixelSize.x, 1 - y * _pixelSize.y);
                glUniform2fv(_positionUniform, 1, &currentPosition[0]);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }       
        }
    }

    ImGui::Begin("Chip8 Screen");
    ImGui::GetWindowDrawList()->AddImage
    (
        (void*)_textureRender, 
        ImGui::GetCursorScreenPos(), 
        ImVec2(ImGui::GetCursorScreenPos().x + _reducedRatio.x, ImGui::GetCursorScreenPos().y + _reducedRatio.y), 
        ImVec2(0, 1),
        ImVec2(1, 0)
    );
    ImGui::End();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Screen::InitializeScreen()
{
    float vertices[] 
    {
        0.0,             0.0,
        _pixelSize.x,    0.0,
        _pixelSize.x,    -_pixelSize.y,
        0.0,             -_pixelSize.y,
    };

    unsigned int indices[]
    { 
        1, 2, 0,
        2, 3, 0
    };  

    unsigned int vao = 0;
    unsigned int vbo = 0;
    unsigned int ebo = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER ,ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureRender, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}