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

    //Load OpenGL
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, Settings::screenWidth, Settings::screenHeight);
    glClearColor(0, 0, 0, 0);

    //Load and init ImGui
    IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(_window, true);
	ImGui_ImplOpenGL3_Init("#version 450");

    //Store gui components
    _guiComponents.reserve(5);
    _guiComponents.push_back(&_cpuInfo);
    _guiComponents.push_back(&_instructionDebug);
    _guiComponents.push_back(&_keyboardHandler);
    _guiComponents.push_back(&_memoryViewer);
    _guiComponents.push_back(&_screen);

   


    //////////////////
    glGenFramebuffers(1, &_fboScreen);
    glBindFramebuffer(GL_FRAMEBUFFER, _fboScreen);
    glClearColor(0.5, 0.5, 0.5, 1.0);

    //glViewport
    glGenTextures(1, &_textureScreen);
    glBindTexture(GL_TEXTURE_2D, _textureScreen);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Settings::screenWidth, Settings::screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    

    //Triangle
    Shader shader("shaders/vertex.vert", "shaders/vertex.frag");
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

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureScreen, 0);
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

        //Render
        glClear(GL_COLOR_BUFFER_BIT);

        //RenderScreen();

        RenderGui();

        glfwSwapBuffers(_window);
    }
    
    glfwDestroyWindow(_window);
}

void Application::RenderGui()
{
    //maybe clear
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    for (size_t i = 0; i < _guiComponents.size(); i++)
    {
        _guiComponents[i]->HandleInterface();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, _fboScreen);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    ImGui::Begin("TEST");
    ImGui::GetWindowDrawList()->AddImage((void*)_textureScreen, ImGui::GetCursorScreenPos(), ImVec2(ImGui::GetCursorScreenPos().x + Settings::screenWidth/2, ImGui::GetCursorScreenPos().y + Settings::screenHeight/2), ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Application::RenderScreen()
{
    glBindFramebuffer(GL_FRAMEBUFFER, _fboScreen);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}