#include "Application.hpp"

Application* Application::_application = nullptr;
Application::Application()
{
    glfwInit();
    _window = glfwCreateWindow(Settings::screenWidth, Settings::screenHeight, Settings::title, NULL, NULL);
    glfwMakeContextCurrent(_window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, Settings::screenWidth, Settings::screenHeight);
    glClearColor(0, 0, 0, 0);

    Shader shader("../resources/shader.vert", "../resources/shader.frag");

    glm::vec3(0, 0, 0);
}

Application* Application::GetInstance() noexcept
{
    if (_application == nullptr)
    {
        _application = new Application();
    }

    return _application;
}

int Application::Run() const noexcept
{
    while (!glfwWindowShouldClose(_window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(_window);
    }
    
    glfwDestroyWindow(_window);
}