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



#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

ViewImpl *ViewImpl::instance = nullptr;



namespace {


    //координаты красных пикселей в слове END
    Point end[34]{ {9,5}, {9,6}, {9,7}, {9,9}, {9,12}, {9,14}, {9,15}, {9,16},
                   {13,5}, {13,6}, {13,7}, {13,9}, {13,12}, {13,14}, {13,15}, {13,16},
                   {10, 5}, {10, 9}, {10, 12}, {10, 14}, {10, 17},
                   {11, 5}, {11, 6}, {11, 9}, {11, 11}, {11, 12}, {11, 14}, {11, 17},
                   {12, 5}, {12, 9}, {12, 10}, {12, 12}, {12, 14}, {12, 17} };
}


void ViewImpl::ShowFruit(ImVec4 Fruit_color) { //fruit
    glBegin(GL_TRIANGLE_FAN);
    glColor4f(Fruit_color.x * Fruit_color.w, Fruit_color.y * Fruit_color.w, Fruit_color.z * Fruit_color.w, Fruit_color.w);
    glColor3f(1,0,0);
    glVertex2f(0.3f, 0.3f);
    glVertex2f(0.3f, 0.7f);
    glVertex2f(0.7f, 0.7f);
    glVertex2f(0.7f, 0.3f);
    glEnd();
}

void ViewImpl::ShowSnake_0(ImVec4 Snake_color) { //snake 0

    glBegin(GL_TRIANGLE_FAN);
    glColor4f(Snake_color.x * Snake_color.w, Snake_color.y * Snake_color.w, Snake_color.z * Snake_color.w, Snake_color.w);
    glVertex2f(0.1f, 0.1f);
    glVertex2f(0.1f, 0.9f);
    glVertex2f(0.9f, 0.9f);
    glVertex2f(0.9f, 0.1f);
    glEnd();

}

void ViewImpl::ShowSnake_o(ImVec4 Snake_color) { //snake o
    glBegin(GL_TRIANGLE_FAN);
    glColor4f(Snake_color.x * Snake_color.w, Snake_color.y * Snake_color.w, Snake_color.z * Snake_color.w, Snake_color.w);
    glVertex2f(0.2f, 0.2f);
    glVertex2f(0.2f, 0.8f);
    glVertex2f(0.8f, 0.8f);
    glVertex2f(0.8f, 0.2f);
    glEnd();

}

void ViewImpl::ShowField(ImVec4 Field_color) { //фон
    glBegin(GL_TRIANGLE_STRIP);
    glColor4f((Field_color.x * Field_color.w), (Field_color.y * Field_color.w), (Field_color.z * Field_color.w), Field_color.w);
    glVertex2f(0, 1);
    glColor4f((Field_color.x * Field_color.w) - 0.1f, (Field_color.y * Field_color.w) - 0.1f, (Field_color.z * Field_color.w) - 0.1f, Field_color.w);
    glVertex2f(1, 1); glVertex2f(0, 0);
    glColor4f((Field_color.x * Field_color.w) - 0.2f, (Field_color.y * Field_color.w) - 0.2f, (Field_color.z * Field_color.w) - 0.2f, Field_color.w);
    glVertex2f(1, 0);
    glEnd();
}



void ViewImpl::ShowBorder(ImVec4 Border_color) { //граница
    glBegin(GL_TRIANGLE_STRIP);
    glColor4f((Border_color.x * Border_color.w), (Border_color.y * Border_color.w), (Border_color.z * Border_color.w), Border_color.w);
    glVertex2f(0, 1);
    glColor4f((Border_color.x * Border_color.w) + 0.1f, (Border_color.y * Border_color.w) + 0.1f, (Border_color.z * Border_color.w) + 0.1f, Border_color.w);
    glVertex2f(1, 1); glVertex2f(0, 0);
    glColor4f((Border_color.x * Border_color.w) + 0.2f, (Border_color.y * Border_color.w) + 0.2f, (Border_color.z * Border_color.w) + 0.2f, Border_color.w);
    glVertex2f(1, 0);
    glEnd();
}

void ViewImpl::ShowEnd() {
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(0, 1);
    glColor3f(0.9f, 0.0f, 0.0f); glVertex2f(1, 1); glVertex2f(0, 0);
    glColor3f(0.8f, 0.0f, 0.0f); glVertex2f(1, 0);
    glEnd();
}


void ViewImpl::Draw() {



    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    //рисовка происходит снизу вверх

    glLoadIdentity();
    glScaled(2.0 / (_model->getGameSize().width + 2), 2.0 / (_model->getGameSize().height + 2), 1);
    glTranslatef(-((float)_model->getGameSize().width + 2.0f) * 0.5f, -((float)_model->getGameSize().height + 2.0f) * 0.5f, 0.0f);

    //нижняя граница
    for (int i = 0; i < _model->getGameSize().width + 2; i++) {
        glPushMatrix();
        glTranslatef((float)i, 0.0f, 0.0f);
        ShowBorder(_model->getBorderColor());
        glPopMatrix();
    }

    //поле
    for (int j = 0; j < _model->getGameSize().height; j++) {
        for (int i = 0; i < _model->getGameSize().width + 2; i++) {
            glPushMatrix();
            glTranslatef((float)i, (float)j + 1, 0.0f);


            if (i == 0 || i == _model->getGameSize().width + 1)
                ShowBorder(_model->getBorderColor());
            else if (j == _model->getY() && i == _model->getX()) {
                ShowField(_model->getFieldColor());
                ShowSnake_0(_model->getSnakeColor());
            }
            else if (j == _model->getFruitY() && i == _model->getFruitX()) {
                ShowField(_model->getFieldColor());
                ShowFruit(_model->getFruitColor());
            }
            else {
                bool print = false;
                for (int k = 0; k < _model->getNTail(); k++) {
                    if (_model->getTailY()[k] == j && _model->getTailX()[k] == i) {
                        ShowField(_model->getFieldColor());
                        ShowSnake_o(_model->getSnakeColor());
                        print = true;
                    }
                }
                if (!print)
                    ShowField(_model->getFieldColor());
            }
            glPopMatrix();
        }
    }

    //верхняя граница
    for (int i = 0; i < _model->getGameSize().width + 2; i++) {
        glPushMatrix();
        glTranslatef((float)i, (float)_model->getGameSize().height + 1, 0.0f);
        ShowBorder(_model->getBorderColor());
        glPopMatrix();
    }

}

void ViewImpl::End() {



    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    glScaled(2.0 / (21.0 + 2.0), 2.0 / (21. + 2.0), 1.0);
    glTranslatef(-((float)21.0 + 2.0f) * 0.5f, -((float)21.0 + 2.0f) * 0.5f, 0.0f);

    //нижняя граница
    for (int i = 0; i < 21 + 2; i++) {
        glPushMatrix();
        glTranslatef((float)i, 0.0f, 0.0f);
        ShowBorder(_model->getBorderColor());
        glPopMatrix();
    }

    //поле
    for (int j = 0; j < 21; j++) {
        for (int i = 0; i < 21 + 2; i++) {
            glPushMatrix();
            glTranslatef((float)i, (float)j + 1.0f, 0.0f);


            if (i == 0 || i == 21 + 1)
                ShowBorder(_model->getBorderColor());
            else {
                bool flag = true;
                for (int k = 0; k < 34; k++) { // 34 - кол-во точек
                    if (end[k].x == i && end[k].y == j + 1) {
                        ShowEnd();
                        flag = false;
                    }
                }
                if (flag) ShowField(_model->getFieldColor());
            }
            glPopMatrix();
        }
    }

    //верхняя граница
    for (int i = 0; i < 21 + 2; i++) {
        glPushMatrix();
        glTranslatef((float)i, (float)21.0 + 1.0f, 0.0f);
        ShowBorder(_model->getBorderColor());
        glPopMatrix();
    }

}




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

            BorderColor = _model->getBorderColor();
            FieldColor = _model->getFieldColor();
            SnakeColor = _model->getSnakeColor();
            FruitColor = _model->getFruitColor();


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
            Draw();

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
            End();
            // Consider adding a small delay here as well for smoother transitions
            glfwSwapBuffers(window);
        }
    }


}

