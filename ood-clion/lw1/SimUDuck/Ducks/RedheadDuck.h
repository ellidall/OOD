#pragma once

#include "../Duck.h"
#include "../FlyStrategy/FlyWithWings.h"
#include "../QuackStrategy/QuackBehavior.h"
#include "../DanceStrategy/MinuetDance.h"
#include <memory>

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(std::make_unique<FlyWithWings>(), std::make_unique<QuackBehavior>(), std::make_unique<MinuetDance>())
	{
	}

	void Display() const override
	{
		std::cout << "I'm redhead duck" << std::endl;
	}
};