
#include "snake.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <gl/GL.h>
#include <math.h>


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (action == GLFW_PRESS) {
        switch (key) {
        case GLFW_KEY_A:
            Snake::instance->SetInputDirection(Snake::left);
            break;
        case GLFW_KEY_D:
            Snake::instance->SetInputDirection(Snake::right);
            break;
        case GLFW_KEY_W:
            Snake::instance->SetInputDirection(Snake::down);
            break;
        case GLFW_KEY_S:
            Snake::instance->SetInputDirection(Snake::up);
            break;
        }
    }
}

int main() {

    GLFWwindow* window;

    Snake game;
    game.Setup();

    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(600, 600, "Snake", NULL, NULL);

    glfwSetKeyCallback(window, key_callback);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        /* Poll for and process events */
        glfwPollEvents();

        if (game.game) {
            game.Draw();
            game.Logic();
            Sleep(200);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

        }
        else {
            game.End();
            Sleep(200);
            glfwSwapBuffers(window);
        }
    }

    
    return 0;
}