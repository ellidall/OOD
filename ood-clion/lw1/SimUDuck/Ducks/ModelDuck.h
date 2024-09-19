#pragma once

#include "../Duck.h"
#include "../FlyStrategy/FlyNoWay.h"
#include "../QuackStrategy/QuackBehavior.h"
#include "../DanceStrategy/NoDance.h"

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(std::make_unique<FlyNoWay>(), std::make_unique<QuackBehavior>(), std::make_unique<NoDance>())
	{
	}

	void Display() const override
	{
		std::cout << "I'm model duck" << std::endl;
	}
};