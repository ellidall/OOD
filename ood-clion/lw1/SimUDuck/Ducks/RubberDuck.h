#pragma once

#include "../Duck.h"
#include "../FlyStrategy/FlyNoWay.h"
#include "../QuackStrategy/SqueakBehavior.h"
#include "../DanceStrategy/NoDance.h"
#include <iostream>

class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(std::make_unique<FlyNoWay>(), std::make_unique<SqueakBehavior>(), std::make_unique<NoDance>())
	{
	}

	void Display() const override
	{
		std::cout << "I'm rubber duck" << std::endl;
	}
};