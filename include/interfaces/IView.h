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

	/*! \brief
	 * Shows chip's settings (for now prints in console)
	 */
	//virtual void showCurrentSettings() = 0;

	/*! \brief
	 * Runs a user interface that helps the user interact with the backlight
	 */
	//virtual void runMenu() = 0;

//	/*! \brief
//	 * Changes level of _brightness
//	 * @param lvl Level of _brightness. Must be set in [0; 100]
//	 */
//	virtual void changeBrightness(int lvl) = 0;

	using Ptr = std::unique_ptr<IView>;
};
