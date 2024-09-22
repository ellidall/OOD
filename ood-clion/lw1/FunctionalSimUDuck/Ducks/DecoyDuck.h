#pragma once

#include "../Duck.h"
#include "../Strategies/FlyBehavior.h"
#include "../Strategies/DanceBehavior.h"
#include "../Strategies/QuackBehavior.h"
#include <iostream>

class DecoyDuck : public Duck
{
public:
	DecoyDuck() : Duck(
        [](){FlyNoWay();},
        [](){MuteQuack();},
        [](){NoDance();}
    ){}

	void Display() const override
	{
		std::cout << "I'm decoy duck" << std::endl;
	}
};