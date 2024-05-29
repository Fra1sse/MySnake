
#include "Model.h"
#include "impl/ModelImpl.h"

IModel::Ptr createModel()
{
	return std::make_shared<ModelImpl>();
}
