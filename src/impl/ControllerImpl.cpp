// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "impl/ControllerImpl.h"

#include <cassert>
#include <iostream>
#include <stdexcept>
/*
namespace
{
constexpr unsigned char BRIGHTNESS_BYTE = static_cast<unsigned char>(0x09);
constexpr unsigned char ACTION_BYTE = static_cast<unsigned char>(0x02);

constexpr unsigned REPORT_LENGTH = 9;
}

namespace ErrorMsg
{
constexpr const char* ChipError = "ErrorMsg: something is wrong with the chip";
}
*/
ControllerImpl::ControllerImpl(std::shared_ptr<IModel> model)
	: _model(std::move(model))
{

}




namespace {
    struct Point {
        int y, x;
    };

    //координаты красных пикселей в слове END
    Point end[34]{ {9,5}, {9,6}, {9,7}, {9,9}, {9,12}, {9,14}, {9,15}, {9,16},
                   {13,5}, {13,6}, {13,7}, {13,9}, {13,12}, {13,14}, {13,15}, {13,16},
                   {10, 5}, {10, 9}, {10, 12}, {10, 14}, {10, 17},
                   {11, 5}, {11, 6}, {11, 9}, {11, 11}, {11, 12}, {11, 14}, {11, 17},
                   {12, 5}, {12, 9}, {12, 10}, {12, 12}, {12, 14}, {12, 17} };
}


void ControllerImpl::ShowFruit(ImVec4 Fruit_color) { //fruit
    glBegin(GL_TRIANGLE_FAN);
    glColor4f(Fruit_color.x * Fruit_color.w, Fruit_color.y * Fruit_color.w, Fruit_color.z * Fruit_color.w, Fruit_color.w);
    glColor3f(1,0,0);
    glVertex2f(0.3f, 0.3f);
    glVertex2f(0.3f, 0.7f);
    glVertex2f(0.7f, 0.7f);
    glVertex2f(0.7f, 0.3f);
    glEnd();
}

void ControllerImpl::ShowSnake_0(ImVec4 Snake_color) { //snake 0

    glBegin(GL_TRIANGLE_FAN);
    glColor4f(Snake_color.x * Snake_color.w, Snake_color.y * Snake_color.w, Snake_color.z * Snake_color.w, Snake_color.w);
    glVertex2f(0.1f, 0.1f);
    glVertex2f(0.1f, 0.9f);
    glVertex2f(0.9f, 0.9f);
    glVertex2f(0.9f, 0.1f);
    glEnd();

}

void ControllerImpl::ShowSnake_o(ImVec4 Snake_color) { //snake o
    glBegin(GL_TRIANGLE_FAN);
    glColor4f(Snake_color.x * Snake_color.w, Snake_color.y * Snake_color.w, Snake_color.z * Snake_color.w, Snake_color.w);
    glVertex2f(0.2f, 0.2f);
    glVertex2f(0.2f, 0.8f);
    glVertex2f(0.8f, 0.8f);
    glVertex2f(0.8f, 0.2f);
    glEnd();

}

void ControllerImpl::ShowField(ImVec4 Field_color) { //фон
    glBegin(GL_TRIANGLE_STRIP);
    glColor4f((Field_color.x * Field_color.w), (Field_color.y * Field_color.w), (Field_color.z * Field_color.w), Field_color.w);
    glVertex2f(0, 1);
    glColor4f((Field_color.x * Field_color.w) - 0.1f, (Field_color.y * Field_color.w) - 0.1f, (Field_color.z * Field_color.w) - 0.1f, Field_color.w);
    glVertex2f(1, 1); glVertex2f(0, 0);
    glColor4f((Field_color.x * Field_color.w) - 0.2f, (Field_color.y * Field_color.w) - 0.2f, (Field_color.z * Field_color.w) - 0.2f, Field_color.w);
    glVertex2f(1, 0);
    glEnd();
}



void ControllerImpl::ShowBorder(ImVec4 Border_color) { //граница
    glBegin(GL_TRIANGLE_STRIP);
    glColor4f((Border_color.x * Border_color.w), (Border_color.y * Border_color.w), (Border_color.z * Border_color.w), Border_color.w);
    glVertex2f(0, 1);
    glColor4f((Border_color.x * Border_color.w) + 0.1f, (Border_color.y * Border_color.w) + 0.1f, (Border_color.z * Border_color.w) + 0.1f, Border_color.w);
    glVertex2f(1, 1); glVertex2f(0, 0);
    glColor4f((Border_color.x * Border_color.w) + 0.2f, (Border_color.y * Border_color.w) + 0.2f, (Border_color.z * Border_color.w) + 0.2f, Border_color.w);
    glVertex2f(1, 0);
    glEnd();
}

void ControllerImpl::ShowEnd() {
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(0, 1);
    glColor3f(0.9f, 0.0f, 0.0f); glVertex2f(1, 1); glVertex2f(0, 0);
    glColor3f(0.8f, 0.0f, 0.0f); glVertex2f(1, 0);
    glEnd();
}

void ControllerImpl::SetupSnake()
{
    _model->setGame( true );
    _model->setDir(stop); //направление

    _model->setX( _model->getGameSize().width / 2 + 1 );
    _model->setY( _model->getGameSize().height / 2 );

    Fruit();

    _model->setPoints( 0 ); //очки
    _model->setNTail( 0 );

    if (!glfwInit())
        _model->setGame(false);
}

void ControllerImpl::Fruit()
{
    srand(time(NULL));
    _model->setFruitX(rand() % _model->getGameSize().width + 1);
    _model->setFruitY(rand() % _model->getGameSize().height );

    if (_model->getFruitX() == _model->getX() && _model->getFruitY() == _model->getY()) Fruit();
    else for (int i = 0; i < _model->getNTail(); i++) {
            if (_model->getTailX()[i] == _model->getFruitX() && _model->getTailY()[i] == _model->getFruitY()) Fruit();
        }
}

void ControllerImpl::Draw() {



    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    //рисовка происходит снизу вверх

    glLoadIdentity();
    glScaled(2.0 / (_model->getGameSize().width + 2), 2.0 / (_model->getGameSize().height + 2), 1);
    glTranslatef(-((float)_model->getGameSize().width + 2.0f) * 0.5f, -((float)_model->getGameSize().height + 2.0f) * 0.5f, 0.0f);

    //нижняя граница
    for (int i = 0; i < _model->getGameSize().width + 2; i++) {
        glPushMatrix();
        glTranslatef((float)i, 0.0f, 0.0f);
        ShowBorder(_model->getBorderColor());
        glPopMatrix();
    }

    //поле
    for (int j = 0; j < _model->getGameSize().height; j++) {
        for (int i = 0; i < _model->getGameSize().width + 2; i++) {
            glPushMatrix();
            glTranslatef((float)i, (float)j + 1, 0.0f);


            if (i == 0 || i == _model->getGameSize().width + 1)
                ShowBorder(_model->getBorderColor());
            else if (j == _model->getY() && i == _model->getX()) {
                ShowField(_model->getFieldColor());
                ShowSnake_0(_model->getSnakeColor());
            }
            else if (j == _model->getFruitY() && i == _model->getFruitX()) {
                ShowField(_model->getFieldColor());
                ShowFruit(_model->getFruitColor());
            }
            else {
                bool print = false;
                for (int k = 0; k < _model->getNTail(); k++) {
                    if (_model->getTailY()[k] == j && _model->getTailX()[k] == i) {
                        ShowField(_model->getFieldColor());
                        ShowSnake_o(_model->getSnakeColor());
                        print = true;
                    }
                }
                if (!print)
                    ShowField(_model->getFieldColor());
            }
            glPopMatrix();
        }
    }

    //верхняя граница
    for (int i = 0; i < _model->getGameSize().width + 2; i++) {
        glPushMatrix();
        glTranslatef((float)i, (float)_model->getGameSize().height + 1, 0.0f);
        ShowBorder(_model->getBorderColor());
        glPopMatrix();
    }

}



void ControllerImpl::Logic() {
    int prevX = _model->getTailX()[0];
    int prevY = _model->getTailY()[0];
    int prev2X, prev2Y;
    _model->getTailX()[0] = _model->getX();
    _model->getTailY()[0] = _model->getY();
    for (int i = 1; i < _model->getNTail(); i++) {
        prev2X = _model->getTailX()[i];
        prev2Y = _model->getTailY()[i];
        _model->getTailX()[i] = prevX;
        _model->getTailY()[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (_model->getDir()) {
        case left:
            _model->setX(_model->getX() - 1);
            break;
        case right:
            _model->setX(_model->getX() + 1);
            break;
        case up:
            _model->setY(_model->getY() - 1);
            break;
        case down:
            _model->setY(_model->getY() + 1);
            break;
        default:
            break;
    }

    //если попал в границу
    if (_model->getX() < 1 || _model->getX() > _model->getGameSize().width || _model->getY() < 0 || _model->getY() > _model->getGameSize().height - 1) {
        _model->setGame(false);
    }

    //если попал в тело
    for (int i = 0; i < _model->getNTail(); i++) {
        if (_model->getTailX()[i] == _model->getX() && _model->getTailY()[i] == _model->getY())
            _model->setGame(false);

    }

    //если попал в фрукт
    if (_model->getFruitX() == _model->getX() && _model->getFruitY() == _model->getY()) {
        _model->setPoints(_model->getPoints() + 10);
        _model->setNTail(_model->getNTail()+ 1);
        Fruit();

    }
}


void ControllerImpl::End() {



    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    glScaled(2.0 / (21.0 + 2.0), 2.0 / (21. + 2.0), 1.0);
    glTranslatef(-((float)21.0 + 2.0f) * 0.5f, -((float)21.0 + 2.0f) * 0.5f, 0.0f);

    //нижняя граница
    for (int i = 0; i < 21 + 2; i++) {
        glPushMatrix();
        glTranslatef((float)i, 0.0f, 0.0f);
        ShowBorder(_model->getBorderColor());
        glPopMatrix();
    }

    //поле
    for (int j = 0; j < 21; j++) {
        for (int i = 0; i < 21 + 2; i++) {
            glPushMatrix();
            glTranslatef((float)i, (float)j + 1.0f, 0.0f);


            if (i == 0 || i == 21 + 1)
                ShowBorder(_model->getBorderColor());
            else {
                bool flag = true;
                for (int k = 0; k < 34; k++) { // 34 - кол-во точек
                    if (end[k].x == i && end[k].y == j + 1) {
                        ShowEnd();
                        flag = false;
                    }
                }
                if (flag) ShowField(_model->getFieldColor());
            }
            glPopMatrix();
        }
    }

    //верхняя граница
    for (int i = 0; i < 21 + 2; i++) {
        glPushMatrix();
        glTranslatef((float)i, (float)21.0 + 1.0f, 0.0f);
        ShowBorder(_model->getBorderColor());
        glPopMatrix();
    }

}

