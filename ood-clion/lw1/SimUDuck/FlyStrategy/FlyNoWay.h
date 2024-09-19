#pragma once

#include "IFlyBehavior.h"
#include <iostream>

class FlyNoWay : public IFlyBehavior
{
public:
	void Fly() override 
	{
		std::cout << "I can't fly" << std::endl;
	}
};