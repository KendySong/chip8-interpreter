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

    Shader shader("../resources/shader.vert", "../resources/shader.frag");

    IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); 
    (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(_window, true);
	ImGui_ImplOpenGL3_Init("#version 450");
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

        ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

        ImGui::Begin("My name is window, ImGUI window");
        ImGui::Text("hello");
		ImGui::End();

        ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(_window);
    }
    
    glfwDestroyWindow(_window);
}