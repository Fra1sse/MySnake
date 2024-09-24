#pragma once

#include <expected>
#include <memory>
#include <string_view>


class IController
{
public:
	virtual ~IController() = default;

    virtual void SetupSnake() = 0;
    virtual void Fruit() = 0;
    virtual void Logic() = 0;

	using Ptr = std::shared_ptr<IController>;
};
