#pragma once

#include <memory>
#include <string_view>

#include "imgui.h"

enum sides { stop = 0, left, right, up, down };

struct Size16 {
    std::uint16_t width;
    std::uint16_t height;
};

struct Size8 {
    std::uint8_t width;
    std::uint8_t height;
};

struct Point {
    int y, x;
};

class IModel
{
public:

    virtual ~IModel() = default;

    virtual bool getGame() const = 0;
    virtual void setGame(bool g) = 0;

    virtual sides getDir() const = 0;
    virtual void setDir(sides d) = 0;

    virtual int getX() const = 0;
    virtual void setX(int value) = 0;

    virtual int getY() const = 0;
    virtual void setY(int value) = 0;

    virtual int getFruitX() const = 0;
    virtual void setFruitX(int value) = 0;

    virtual int getFruitY() const = 0;
    virtual void setFruitY(int value) = 0;

    virtual int getPoints() const = 0;
    virtual void setPoints(int value) = 0;

    virtual int* getTailX() const = 0;

    virtual int* getTailY() const = 0;

    virtual int getNTail() const = 0;
    virtual void setNTail(int value) = 0;

    virtual Size16 getMenuSize() const = 0;
    virtual void setMenuSize(const Size16& size) = 0;

    virtual Size16 getWindowSize() const = 0;
    virtual void setWindowSize(const Size16& size) = 0;

    virtual Size8 getGameSize() const = 0;
    virtual void setGameSize(const Size8& size) = 0;

    virtual ImVec4 getClearColor() const = 0;
    virtual void setClearColor(const ImVec4& color) = 0;

    virtual ImVec4 getBorderColor() const = 0;
    virtual void setBorderColor(const ImVec4& color) = 0;

    virtual ImVec4 getFieldColor() const = 0;
    virtual void setFieldColor(const ImVec4& color) = 0;

    virtual ImVec4 getFruitColor() const = 0;
    virtual void setFruitColor(const ImVec4& color) = 0;

    virtual ImVec4 getSnakeColor() const = 0;
    virtual void setSnakeColor(const ImVec4& color) = 0;

    virtual bool getBeginGame() const = 0;
    virtual void setBeginGame(bool value) = 0;

    virtual bool getSetup() const = 0;
    virtual void setSetup(bool value) = 0;

    virtual bool getEndMenu() const = 0;
    virtual void setEndMenu(bool value) = 0;

    using Ptr = std::shared_ptr<IModel>;
};
