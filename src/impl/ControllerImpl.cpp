#include "impl/ControllerImpl.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

ControllerImpl::ControllerImpl(std::shared_ptr<IModel> model)
	: _model(std::move(model))
{
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

void ControllerImpl::Logic() 
{
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