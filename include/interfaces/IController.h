#pragma once

#include <expected>
#include <memory>
#include <string_view>


/*! \brief
 *
 * Interface for interacting with the chip that
 * allows to change the keyboard backlight settings
 */
class IController
{
public:
	virtual ~IController() = default;
	/*! \brief
	 * Sends data to chip to change _brightness of backlight
	 * \param lvl Level of _brightness [0; 100]
	 */
	//virtual void setBrightness(int lvl) = 0;

    virtual void SetupSnake() = 0;

    virtual void Fruit() = 0;
    virtual void Draw() = 0;
    virtual void Logic() = 0;
    virtual void End() = 0;

	using Ptr = std::shared_ptr<IController>;
};
