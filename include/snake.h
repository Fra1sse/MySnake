#pragma once


#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "snake.h"
//#include "Menu.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <gl/GL.h>
#include <math.h>


struct Size16
{
	std::uint16_t width;
	std::uint16_t height;
};

struct Size8
{
	std::uint8_t width;
	std::uint8_t height;
};

class Menu {
public:

	int BeginMenu();


	Size16& getWindowSize()
	{
		return _windowSize;
	}
	
	Size8& getGameSize()
	{
		return _gameSize;
	}

	ImVec4 getBorder_color() {
		return Border_color;
	}

	ImVec4 getField_color() {
		return Field_color;
	}

	ImVec4 getFruit_color() {
		return Fruit_color;
	}

	ImVec4 getSnake_color() {
		return Snake_color;
	}

	bool getBeginGame() {
		return BeginGame;
	}

private:


	Size16 _menuSize;
	Size16 _windowSize;
	Size8 _gameSize;

	ImVec4 clear_color;
	ImVec4 Border_color;
	ImVec4 Field_color;
	ImVec4 Fruit_color;
	ImVec4 Snake_color;

	bool BeginGame; //изменится при нажатии "play"
	bool Setup; //изменяется при нажатии кнопки "Setup"; показывает состояние окна настроек
	bool EndMenu;


	void SetupMenu(); //для значения экрана меню (высота, длина, цвет(?))
	void SetupGame(); //для значений настроек игры

};





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
	int width, height;
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