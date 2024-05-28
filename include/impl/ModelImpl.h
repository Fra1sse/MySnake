#pragma once

#include "interfaces/IModel.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <gl/GL.h>
#include <math.h>


class ModelImpl : public IModel {
public:


    /*! \brief
     * throws std::runtime_error()
     */
    ModelImpl();

    ~ModelImpl() override;

    ModelImpl(const ModelImpl &) = delete;

    ModelImpl &operator=(const ModelImpl &) = delete;

    /*hid_device* getChipHandler() override;
    int getBrightness() override;*/

    bool getGame() const override { return game; }

    void setGame(bool g) override { game = g; }

    sides getDir() const override { return dir; }

    void setDir(sides d) override { dir = static_cast<sides>(d); }

    int getX() const override { return x; }

    void setX(int value) override { x = value; }

    int getY() const override { return y; }

    void setY(int value) override { y = value; }

    int getFruitX() const override { return fruitX; }

    void setFruitX(int value) override { fruitX = value; }

    int getFruitY() const override { return fruitY; }

    void setFruitY(int value) override { fruitY = value; }

    int getPoints() const override { return points; }

    void setPoints(int value) override { points = value; }

    int *getTailX() const override { return tailX; }


    int *getTailY() const override { return tailY; }


    int getNTail() const override { return ntail; }

    void setNTail(int value) override { ntail = value; }

    Size16 getMenuSize() const override { return _menuSize; }

    void setMenuSize(const Size16 &size) override { _menuSize = size; }

    Size16 getWindowSize() const override { return _windowSize; }

    void setWindowSize(const Size16 &size) override { _windowSize = size; }

    Size8 getGameSize() const override { return _gameSize; }

    void setGameSize(const Size8 &size) override { _gameSize = size; }

    ImVec4 getClearColor() const override { return ClearColor; }

    void setClearColor(const ImVec4 &color) override { ClearColor = color; }

    ImVec4 getBorderColor() const override { return BorderColor; }

    void setBorderColor(const ImVec4 &color) override { BorderColor = color; }

    ImVec4 getFieldColor() const override { return FieldColor; }

    void setFieldColor(const ImVec4 &color) override { FieldColor = color; }

    ImVec4 getFruitColor() const override { return FruitColor; }

    void setFruitColor(const ImVec4 &color) override { FruitColor = color; }

    ImVec4 getSnakeColor() const override { return SnakeColor; }

    void setSnakeColor(const ImVec4 &color) override { SnakeColor = color; }

    bool getBeginGame() const override { return BeginGame; }

    void setBeginGame(bool value) override { BeginGame = value; }

    bool getSetup() const override { return Setup; }

    void setSetup(bool value) override { Setup = value; }

    bool getEndMenu() const override { return EndMenu; }

    void setEndMenu(bool value) override { EndMenu = value; }





private:


    void SetInputDirection(sides direction);

    bool game;
    sides dir;
    int x, y;
    int fruitX, fruitY;
    int points; //441 441
    int ntail;
    int* tailX;
    int* tailY;

    Size16 _menuSize;
    Size16 _windowSize;
    Size8 _gameSize;

    bool BeginGame;
    bool Setup;
    bool EndMenu;


    ImVec4 ClearColor;
    ImVec4 BorderColor;
    ImVec4 FieldColor;
    ImVec4 FruitColor;
    ImVec4 SnakeColor;


    /*hid_device* _dev; // todo: change to ref?
    int _brightness;*/
};