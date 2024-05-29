
#include "View.h"
#include "impl/ViewImpl.h"
#include "interfaces/IController.h"

IView::Ptr createView(IController::Ptr c_ptr, IModel::Ptr m_ptr)
{
	return std::make_unique<ViewImpl>(std::move(c_ptr), std::move(m_ptr));
}