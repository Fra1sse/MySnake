#pragma once

#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include <math.h>

#include <iostream>
#include <conio.h>
#include <windows.h>




class Snake {
public:
	void Setup();
	void Fruit();
	void Draw();
	void Logic();
	void End();

	enum sides { stop = 0, left, right, up, down };
	void SetInputDirection(sides direction);

	bool game;


	static Snake* instance;

	Snake();
	~Snake() {};
private:
	void ShowBorder();
	void ShowSnake0();
	void ShowFruit();
	void ShowField();
	void ShowSnake();
	void ShowEnd();
	
	sides dir;
	int x, y;
	int width, height;
	int fruitX, fruitY;
	int points;
	int tailX[441], tailY[441], ntail;

	
};