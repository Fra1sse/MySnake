// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "Model.h"
#include "impl/ModelImpl.h"

IModel::Ptr createModel()
{
	return std::make_shared<ModelImpl>();
}
