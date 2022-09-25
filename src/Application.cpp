#include "Application.hpp"

Application* Application::_application = nullptr;

void GetKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    CPU::GetInstance()->SetKeyInput(scancode, action);  
}

Application::Application()
{
    _fps = 0;

    //Create and configure window
    glfwInit();
    _window = glfwCreateWindow(Settings::windowWidth, Settings::windowHeight, Settings::title, NULL, NULL);
    glfwWindowHint(GL_MINOR_VERSION, 4);
    glfwWindowHint(GL_MAJOR_VERSION, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwSetKeyCallback(_window, GetKeyInput);
    glfwMakeContextCurrent(_window);

    //Load OpenGL and shaders
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    Shader _shader("shaders/vertex.vert", "shaders/vertex.frag");
    glViewport(0, 0, Settings::windowWidth, Settings::windowHeight);

    //Load and init ImGui
    IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
    ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = true;
	ImGui_ImplGlfw_InitForOpenGL(_window, true);
	ImGui_ImplOpenGL3_Init("#version 450");

    //Init and store gui components  
    _screen.Init(_shader.GetProgram());
    _screen.InitializeScreen();

    _guiComponents.reserve(7);
    _guiComponents.push_back(&_cpuInfo);
    _guiComponents.push_back(&_disassembler);
    _guiComponents.push_back(&_keyboardHandler);
    _guiComponents.push_back(&_memoryViewer);
    _guiComponents.push_back(&_menu);
    _guiComponents.push_back(&_screen); 
    _guiComponents.push_back(&_stackViewer);
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

        //Count fps
        _fps++;
        if (_timer.GetElapsedTime() > 1000)
        {
            _menu.SetFPS(_fps);
            _fps = 0;
            _timer.Restart();
        }

        CPU::GetInstance()->Update();

        //Render       
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ConsoleLog::GetInstance()->HandleInterface();
        for (size_t i = 0; i < _guiComponents.size(); i++)
        {
            _guiComponents[i]->HandleInterface();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(_window);
    }
    
    glfwDestroyWindow(_window);
    delete _application;
    
    return EXIT_SUCCESS;
}