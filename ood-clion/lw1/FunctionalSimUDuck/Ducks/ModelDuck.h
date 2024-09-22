#pragma once

#include "../Duck.h"
#include "../Strategies/FlyBehavior.h"
#include "../Strategies/QuackBehavior.h"
#include "../Strategies/DanceBehavior.h"
#include <iostream>

class ModelDuck : public Duck
{
public:
    ModelDuck() : Duck(
        [](){FlyNoWay();},
        [](){SimpleQuack();},
        [](){NoDance();}
    ){}

	void Display() const override
	{
		std::cout << "I'm model duck" << std::endl;
	}
};