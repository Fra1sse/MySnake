#pragma once

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




class Snake {
public:
	void GameBegin();

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

	static Snake* instance;

	Snake();
	~Snake() {};
private:

	Menu _setup;


	//движение
	enum sides { stop = 0, left, right, up, down };
	void SetInputDirection(sides direction);
	bool game;
	sides dir;
	int x, y;
	int fruitX, fruitY;
	int points;
	int tailX[441], tailY[441], ntail;

	
	void SetupSnake();
	void Fruit();
	void Draw();
	void Logic();
	void End();

	//рисовка
	void ShowBorder(ImVec4 Border_color);
	void ShowSnake_0(ImVec4 Snake_color);
	void ShowFruit(ImVec4 Fruit_color);
	void ShowField(ImVec4 Field_color);
	void ShowSnake_o(ImVec4 Snake_color);
	void ShowEnd();

};