#pragma once

#include "../Duck.h"
#include "../Strategies/FlyBehavior.h"
#include "../Strategies/QuackBehavior.h"
#include "../Strategies/DanceBehavior.h"
#include <iostream>

class RedheadDuck : public Duck
{
public:
    RedheadDuck() : Duck(
        [](){FlyWithWings();},
        [](){SimpleQuack();},
        [](){MinuetDance();}
    ){}

	void Display() const override
	{
		std::cout << "I'm redhead duck" << std::endl;
	}
};