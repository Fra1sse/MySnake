#pragma once

#include "interfaces/IController.h"
#include "interfaces/IModel.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Menu.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <gl/GL.h>
#include <math.h>



class ControllerImpl : public IController
{

public:
	explicit ControllerImpl(std::shared_ptr<IModel>);

    void GameBegin();

    void SetupSnake() override;

    void Fruit() override;
    void Draw() override;
    void Logic() override;
    void End() override;

	/*void setBrightness(int lvl) override;*/
private:
	std::shared_ptr<IModel> _model;





    //рисовка
    void ShowBorder(ImVec4 Border_color);
    void ShowSnake_0(ImVec4 Snake_color);
    void ShowFruit(ImVec4 Fruit_color);
    void ShowField(ImVec4 Field_color);
    void ShowSnake_o(ImVec4 Snake_color);
    void ShowEnd();
};
