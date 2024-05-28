#pragma once

#include "interfaces/IView.h"

IView::Ptr createView(IController::Ptr controller, IModel::Ptr model);