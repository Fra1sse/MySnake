#pragma once
 
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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

	ImVec4 getBorderColor() {
		return BorderColor;
	}

	ImVec4 getFieldColor() {
		return FieldColor;
	}

	ImVec4 getFruitColor() {
		return FruitColor;
	}

	ImVec4 getSnakeColor() {
		return SnakeColor;
	}

	bool getBeginGame() {
		return BeginGame;
	}

private:


	Size16 _menuSize;
	Size16 _windowSize;
	Size8 _gameSize;

	ImVec4 ClearColor;
	ImVec4 BorderColor;
	ImVec4 FieldColor;
	ImVec4 FruitColor;
	ImVec4 SnakeColor;

	bool BeginGame; 
	bool Setup;
	bool EndMenu;


	void SetupMenu();
	void SetupGame(); 

};