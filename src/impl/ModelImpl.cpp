#include <cassert>
#include <iostream>
#include <stdexcept>

#include "impl/ModelImpl.h"

ModelImpl::ModelImpl()
{
    tailX = static_cast<int*>(calloc(441, sizeof(int)));
    tailY = static_cast<int*>(calloc(441, sizeof(int)));
}

ModelImpl::~ModelImpl()
{
    free(tailX);
    free(tailY);
}

void ModelImpl::SetInputDirection(sides direction)
{
    dir = direction;
}
