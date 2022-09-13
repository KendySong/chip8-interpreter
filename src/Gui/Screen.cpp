#include "Screen.hpp"

void Screen::Init()
{
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

    InitializeScreen();
}

void Screen::HandleInterface()
{
    glBindFramebuffer(GL_FRAMEBUFFER, _fbRender);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);

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
    //Triangle
    float vertices[]
    {
         0.0,  0.5, 0.0,
         0.5, -0.5, 0.0,
        -0.5, -0.5, 0.0
    };

    unsigned int vao = 0;
    unsigned int vbo = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureRender, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}