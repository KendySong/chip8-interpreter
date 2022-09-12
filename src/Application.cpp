#include "Application.hpp"

Application* Application::_application = nullptr;
Application::Application()
{
    //Create and configure window
    glfwInit();
    _window = glfwCreateWindow(Settings::screenWidth, Settings::screenHeight, Settings::title, NULL, NULL);
    glfwWindowHint(GL_MINOR_VERSION, 4);
    glfwWindowHint(GL_MAJOR_VERSION, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwMakeContextCurrent(_window);

    //Load OpenGL and shaders
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    Shader shader("shaders/vertex.vert", "shaders/vertex.frag");
    glViewport(0, 0, Settings::screenWidth, Settings::screenHeight);

    //Load and init ImGui
    IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
    ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = true;
	ImGui_ImplGlfw_InitForOpenGL(_window, true);
	ImGui_ImplOpenGL3_Init("#version 450");

    //Init and store gui components
    _screen.Init();
    _guiComponents.reserve(5);
    _guiComponents.push_back(&_consoleLog);
    _guiComponents.push_back(&_cpuInfo);
    _guiComponents.push_back(&_instructionDebug);
    _guiComponents.push_back(&_keyboardHandler);
    _guiComponents.push_back(&_memoryViewer);
    _guiComponents.push_back(&_menu);
    _guiComponents.push_back(&_screen);
}

Application* Application::GetInstance() noexcept
{
    if (_application == nullptr)
    {
        _application = new Application();
    }

    return _application;
}

int Application::Run()
{
    //Main loop
    while (!glfwWindowShouldClose(_window))
    {
        glfwPollEvents();
    
        RenderGui();
        glfwSwapBuffers(_window);
    }
    
    glfwDestroyWindow(_window);
}

void Application::RenderGui()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    for (size_t i = 0; i < _guiComponents.size(); i++)
    {
        _guiComponents[i]->HandleInterface();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}