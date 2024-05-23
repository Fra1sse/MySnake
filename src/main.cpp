#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Menu.h"
#include "snake.h"
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <gl/GL.h>
#include <math.h>





int main() {


    Snake game;
    game.GameBegin();
    
    
    return 0;
}