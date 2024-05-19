#pragma once
 
/*
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "snake.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <gl/GL.h>
#include <math.h>

struct Size
{
	std::uint16_t width;
	int Height;
};

class Menu {
public:
	int BeginMenu();


	ImVec4 Border_color;
	ImVec4 Field_color;
	ImVec4 Fruit_color;
	ImVec4 Snake_color;
	Size& getSize()
	{
		return _windowSize;
	}
	Size _windowSize;
	int WidthWindow;
	int HeightWindow; //для исменения размера окна игры
	int WidthGame, HeightGame; //для изменения размера поля игры

private:
	void SetupMenu(); //значения экрана меню (высота, длина, цвет(?))
	void SetupGame(); //для значений настроек игры

	ImVec4 clear_color;
	int WidthMenu, HeightMenu; //константное значение размера меню


	bool Setup; //изменяется при нажатии кнопки; показывает состояние окна настроек
	bool BeginGame; //изменится при нажатии "play"
	bool EndMenu;

};

*/