// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <cstring>
#include <iomanip>
#include <limits>
#include <chrono>
#include <thread>

#include "impl/ViewImpl.h"

/*
namespace
{
constexpr char CHANGE_BRIGHTNESS = 'b';
constexpr char QUIT = 'q';
}
*/


#include "Menu.h"

#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

ViewImpl *ViewImpl::instance = nullptr;

void ViewImpl::SetupMenu() {

    _model->setMenuSize({1200, 600});

    _model->setClearColor(ImVec4(0.45f, 0.55f, 0.60f, 1.00f));

    _model->setSetup(false);
    _model->setEndMenu(false);
    _model->setBeginGame(false);
}

void ViewImpl::SetupGame() {


    _model->setWindowSize({600, 600});

    _model->setGameSize({20, 20});

    _model->setBorderColor(ImVec4(0.0f, 0.0f, 0.0f, 1.00f));
    _model->setFieldColor(ImVec4(0.8f, 0.8f, 0.8f, 1.00f));
    _model->setFruitColor(ImVec4(1.0f, 0.0f, 0.0f, 1.00f));
    _model->setSnakeColor(ImVec4(0.0f, 1.0f, 0.0f, 1.00f));

}


int ViewImpl::BeginMenu() {

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
    const char *glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    GLFWwindow *window = glfwCreateWindow(_model->getMenuSize().width, _model->getMenuSize().height, "Snake", nullptr,
                                          nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
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
    while (!glfwWindowShouldClose(window) && !_model->getBeginGame() && !_model->getEndMenu())
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
                _model->setBeginGame(true);
            if (ImGui::Button("Setup Game"))
                _model->setSetup(true);
            if (ImGui::Button("Close Menu"))
                _model->setEndMenu(true);
            ImGui::End();
        }

        if (_model->getSetup()) {
            bool setup = _model->getSetup();
            int temp_width = _model->getGameSize().width;
            int temp_height = _model->getGameSize().height;

            ImVec4 BorderColor, FieldColor, SnakeColor, FruitColor;

            ImGui::Begin("Setup Game", &setup);
            ImGui::SliderInt("width_game", &temp_width, 2, 21);
            ImGui::SliderInt("height_game", &temp_height, 2, 21);


            ImGui::ColorEdit3("Border color", (float *) &BorderColor);
            ImGui::ColorEdit3("Field color", (float *) &FieldColor);
            ImGui::ColorEdit3("Snake color", (float *) &SnakeColor);
            ImGui::ColorEdit3("Fruit color", (float *) &FruitColor);

            if (ImGui::Button("Close"))
                _model->setSetup(false);
            ImGui::End();

            _model->setSetup(setup);
            _model->setGameSize({static_cast<std::uint8_t>(temp_width), static_cast<std::uint8_t>(temp_height)});
            _model->setBorderColor(BorderColor);
            _model->setFieldColor(FieldColor);
            _model->setSnakeColor(SnakeColor);
            _model->setFruitColor(FruitColor);

        }


        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        auto ClearColor = _model->getClearColor();

        glClearColor(ClearColor.x * ClearColor.w, ClearColor.y * ClearColor.w, ClearColor.z * ClearColor.w,
                     ClearColor.w);
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


ViewImpl::ViewImpl(std::shared_ptr<IController> controller, std::shared_ptr<IModel> model)
        : _controller(std::move(controller)), _model(std::move(model)) {
    instance = this;
}

void ViewImpl::key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (action == GLFW_PRESS) {

        switch (key) {
            case GLFW_KEY_A:
                ViewImpl::instance->SetInputDirection(left);
                break;
            case GLFW_KEY_D:
                ViewImpl::instance->SetInputDirection(right);
                break;
            case GLFW_KEY_W:
                ViewImpl::instance->SetInputDirection(down);
                break;
            case GLFW_KEY_S:
                ViewImpl::instance->SetInputDirection(up);
                break;
        }
    }
}

void ViewImpl::SetInputDirection(sides direction) {
    _model->setDir(direction);
}


void ViewImpl::draw() {
    BeginMenu();


    _controller->SetupSnake();


    if (!_model->getBeginGame()) {
        return;
    }
    GLFWwindow *window;
    window = glfwCreateWindow(_model->getWindowSize().width, _model->getWindowSize().height, "Snake", NULL, NULL);
    glfwSetKeyCallback(window, key_callback);
    if (!window) {
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    // Target update rate
    const int targetUpdateDelay = 10.0;
    const double targetUpdateTime = 1.0 / targetUpdateDelay;

    
// Target FPS and calculated frame time
    const int targetFPS = 155;
    const double targetFrameTime = 1.0 / targetFPS;

// For timing the game loop
    std::chrono::high_resolution_clock::time_point lastUpdateTime = std::chrono::high_resolution_clock::now();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Calculate time since last frame
        auto currentTime = std::chrono::high_resolution_clock::now();
        double deltaTime = std::chrono::duration<double>(currentTime - lastUpdateTime).count();

        if (_model->getGame()) {
            _controller->Draw();

            // Only update logic if enough time has passed
            if (deltaTime >= targetUpdateTime) {
                _controller->Logic();
                lastUpdateTime = currentTime; // Reset timer
            }

            // Calculate sleep time to achieve target FPS
            double frameTime = std::chrono::duration<double>(
                    std::chrono::high_resolution_clock::now() - currentTime).count();
            double sleepTime = targetFrameTime - frameTime;

            // Sleep if there's time left in the frame
            if (sleepTime > 0.0) {
                std::this_thread::sleep_for(std::chrono::duration<double>(sleepTime));
            }

            glfwSwapBuffers(window);
        } else {
            _controller->End();
            // Consider adding a small delay here as well for smoother transitions
            glfwSwapBuffers(window);
        }
    }


}

