#pragma once

#include "interfaces/IController.h"
#include "interfaces/IModel.h"

/*! \brief
 *
 * Interface for interacting with user
 */
class IView
{
public:
	virtual ~IView() = default;

    virtual void draw() = 0;
    virtual void Draw() = 0;
    virtual void End() = 0;

	using Ptr = std::unique_ptr<IView>;
};
