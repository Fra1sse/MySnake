
#include "Controller.h"
#include "impl/ControllerImpl.h"

IController::Ptr createController(IModel::Ptr ptr)
{
	return std::make_shared<ControllerImpl>(std::move(ptr));
}