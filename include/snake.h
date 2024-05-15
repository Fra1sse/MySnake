#pragma once


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

class Menu {
public:
	int BeginMenu();

	ImVec4 clear_color;
	ImVec4 Border_color;
	ImVec4 Field_color;
	ImVec4 Fruit_color;
	ImVec4 Snake_color;
	int WidthWindow, HeightWindow;
	int WidthGame, HeightGame; //для изменения размера поля игры

private:
	void SetupMenu(); //значения экрана меню (высота, длина, цвет(?))
	void SetupGame(); //для значений настроек игры


	int WidthMenu, HeightMenu; //константное значение размера меню
	

	bool Setup; //изменяется при нажатии кнопки; показывает состояние окна настроек
	bool BeginGame; //изменится при нажатии "play"
	bool EndMenu;
	

};




class Snake {
public:
	void GameBegin();
	//void glfwSetKeyCallback(GLFWwindow* window, GLFWkeyfun	callback);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

	static Snake* instance;

	Snake();
	~Snake() {};
private:
	Menu setup;
	void SetupSnake();
	void Fruit();
	void Draw();
	void Logic();
	void End();

	enum sides { stop = 0, left, right, up, down };
	void SetInputDirection(sides direction);

	bool game;




	void ShowBorder(ImVec4 Border_color);
	void ShowSnake_0(ImVec4 Snake_color);
	void ShowFruit(ImVec4 Fruit_color); 
	void ShowField(ImVec4 Field_color);
	void ShowSnake_o(ImVec4 Snake_color);
	void ShowEnd();
	
	sides dir;
	int x, y;
	int width, height;
	int fruitX, fruitY;
	int points;
	int tailX[441], tailY[441], ntail;

	
};