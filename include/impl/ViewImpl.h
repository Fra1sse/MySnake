#pragma once

#include <memory>

#include "interfaces/IView.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <gl/GL.h>
#include <math.h>



class ViewImpl : public IView
{
public:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

    void SetInputDirection(sides direction);

	ViewImpl(std::shared_ptr<IController> controller, std::shared_ptr<IModel>);

    void draw() override;

    int BeginMenu();

    static ViewImpl* instance;

    void Draw() override;
    void End() override;

    /*void showCurrentSettings() override;
    void runMenu() override;*/
//	void changeBrightness(int lvl) override;

private:
	std::shared_ptr<IController> _controller;
	std::shared_ptr<IModel> _model;

    //рисовка
    void ShowBorder(ImVec4 Border_color);
    void ShowSnake_0(ImVec4 Snake_color);
    void ShowFruit(ImVec4 Fruit_color);
    void ShowField(ImVec4 Field_color);
    void ShowSnake_o(ImVec4 Snake_color);
    void ShowEnd();

    void SetupMenu();
    void SetupGame();
};
