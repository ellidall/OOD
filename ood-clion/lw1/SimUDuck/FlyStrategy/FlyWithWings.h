#pragma once

#include "IFlyBehavior.h"
#include <iostream>

class FlyWithWings : public IFlyBehavior
{
public:
    FlyWithWings() : IFlyBehavior(true) {}

	void Fly() override
	{
		std::cout << "I'm flying with wings!!" << std::endl;
        m_flightCount++;
	}
};