#include "snake.h"
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

void Menu::SetupMenu() {

	WidthMenu = 1200;
	HeightMenu = 600;
    clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	Setup = false;
	EndMenu = false;
	BeginGame = false;
}

void Menu::SetupGame() {


    WidthWindow = 600;
    HeightWindow = 600;

    Border_color = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
    Field_color = ImVec4(0.8f, 0.8f, 0.8f, 1.00f);
    Fruit_color = ImVec4(1.0f, 0.0f, 0.0f, 1.00f);
    Snake_color = ImVec4(0.0f, 1.0f, 0.0f, 1.00f);
    WidthGame = 11;
    HeightGame = 11;
}




int Menu::BeginMenu() {

    SetupMenu();
    SetupGame();
    std::cout << WidthWindow << std::endl;

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

    // Create window with graphics context
        GLFWwindow* window = glfwCreateWindow(WidthMenu, HeightMenu, "Snake", nullptr, nullptr);
        if (window == nullptr)
            return 1;
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1); // Enable vsync

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
#ifdef __EMSCRIPTEN__
        ImGui_ImplGlfw_InstallEmscriptenCanvasResizeCallback("#canvas");
#endif
        ImGui_ImplOpenGL3_Init(glsl_version);

        // Our state
        bool show_demo_window = false;
        Setup = false;
        
       

        // Main loop
#ifdef __EMSCRIPTEN__
    // For an Emscripten build we are disabling file-system access, so let's not attempt to do a fopen() of the imgui.ini file.
    // You may manually call LoadIniSettingsFromMemory() to load settings from your own storage.
        io.IniFilename = nullptr;
        EMSCRIPTEN_MAINLOOP_BEGIN
#else
        while (!glfwWindowShouldClose(window) && !BeginGame && !EndMenu)
#endif
        {
            glfwPollEvents();

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
            if (show_demo_window)
                ImGui::ShowDemoWindow(&show_demo_window);

            // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
            {
                static int counter = 0;

                ImGui::Begin("Menu");                          // Create a window called "Hello, world!" and append into it.

                ImGui::Text("Snake");               // Display some text (you can use a format strings too)

                //кнопки:
                //ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
                //ImGui::Checkbox("Another Window", &show_another_window);

                if (ImGui::Button("Play"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                    BeginGame = true;
                
                if (ImGui::Button("Setup Game"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                    Setup = true;

                if (ImGui::Button("Clouse Menu"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                    EndMenu = true;
                //ImGui::SameLine();
                //ImGui::Text("counter = %d", counter);

                //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
                ImGui::End();
            }

            if (Setup)
            {

                ImGui::Begin("Setup Game", &Setup);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
                //ImGui::Text("Hello from another window!");
                ImGui::SliderInt("width", &WidthGame, 2, 21);            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::SliderInt("height", &HeightGame, 2, 21);            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::ColorEdit3("Border color", (float*)&Border_color); // Edit 3 floats representing a color
                ImGui::ColorEdit3("Field color", (float*)&Field_color); // Edit 3 floats representing a color
                ImGui::ColorEdit3("Snake color", (float*)&Snake_color); // Edit 3 floats representing a color
                ImGui::ColorEdit3("Fruit color", (float*)&Fruit_color); // Edit 3 floats representing a color

                if (ImGui::Button("Close"))
                    Setup = false;
                ImGui::End();
            }

            // Rendering
            ImGui::Render();
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
        }
#ifdef __EMSCRIPTEN__
        EMSCRIPTEN_MAINLOOP_END;
#endif

        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(window);
        glfwTerminate();
        
        if (BeginGame) {
            Snake game;
            game.GameBegin();
        }

        return 0;

}