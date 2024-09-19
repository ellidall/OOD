#pragma once

#include "../Duck.h"
#include "../FlyStrategy/FlyWithWings.h"
#include "../QuackStrategy/QuackBehavior.h"
#include "../DanceStrategy/WaltzDance.h"

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(std::make_unique<FlyWithWings>(), std::make_unique<QuackBehavior>(), std::make_unique<WaltzDance>())
	{
	}

	void Display() const override
	{
		std::cout << "I'm mallard duck" << std::endl;
	}
};