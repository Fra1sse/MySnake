#include "Menu.h"
#include "snake.h"
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

void Menu::SetupMenu() {

	_menuSize.width = 1200;
	_menuSize.height = 600;
    ClearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	Setup = false;
	EndMenu = false;
	BeginGame = false;
}

void Menu::SetupGame() {

    _windowSize.width = 600;
    _windowSize.height = 600;

    _gameSize.width = 2;
    _gameSize.height = 2;

    BorderColor = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
    FieldColor = ImVec4(0.8f, 0.8f, 0.8f, 1.00f);
    FruitColor = ImVec4(1.0f, 0.0f, 0.0f, 1.00f);
    SnakeColor = ImVec4(0.0f, 1.0f, 0.0f, 1.00f);
}


int Menu::BeginMenu() {

    SetupMenu();
    SetupGame();

        if (!glfwInit())
            return 1;

        // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
        const char* glsl_version = "#version 100";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
        const char* glsl_version = "#version 150";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
        const char* glsl_version = "#version 130";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

        GLFWwindow* window = glfwCreateWindow(_menuSize.width, _menuSize.height, "Snake", nullptr, nullptr);
        if (window == nullptr)
            return 1;
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
#ifdef __EMSCRIPTEN__
        ImGui_ImplGlfw_InstallEmscriptenCanvasResizeCallback("#canvas");
#endif
        ImGui_ImplOpenGL3_Init(glsl_version);
#ifdef __EMSCRIPTEN__
        io.IniFilename = nullptr;
        EMSCRIPTEN_MAINLOOP_BEGIN
#else
        while (!glfwWindowShouldClose(window) && !BeginGame && !EndMenu)
#endif
        {
            glfwPollEvents();
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            {
                ImGui::Begin("Menu");
                ImGui::Text("Snake");       

                if (ImGui::Button("Play"))                       
                    BeginGame = true;
                if (ImGui::Button("Setup Game"))                         
                    Setup = true;
                if (ImGui::Button("Clouse Menu"))                         
                    EndMenu = true;
                ImGui::End();
            }

            if (Setup)
            {
                ImGui::Begin("Setup Game", &Setup); 
                int temp_width = _gameSize.width, temp_height = _gameSize.height;
                ImGui::SliderInt("width_game", &temp_width, 2, 21);          
                ImGui::SliderInt("height_game", &temp_height, 2, 21);   
                _gameSize.width = (uint8_t)temp_width;
                _gameSize.height = (uint8_t)temp_height;
                ImGui::ColorEdit3("Border color", (float*)&BorderColor); 
                ImGui::ColorEdit3("Field color", (float*)&FieldColor); 
                ImGui::ColorEdit3("Snake color", (float*)&SnakeColor); 
                ImGui::ColorEdit3("Fruit color", (float*)&FruitColor); 

                if (ImGui::Button("Close"))
                    Setup = false;
                ImGui::End();
            }

            
            ImGui::Render();
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(ClearColor.x * ClearColor.w, ClearColor.y * ClearColor.w, ClearColor.z * ClearColor.w, ClearColor.w);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(window);
        }
#ifdef __EMSCRIPTEN__
        EMSCRIPTEN_MAINLOOP_END;
#endif
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(window);
        glfwTerminate();
        

        return 0;
}