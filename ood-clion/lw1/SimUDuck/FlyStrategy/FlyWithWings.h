#pragma once

#include "IFlyBehavior.h"
#include <iostream>

class FlyWithWings : public IFlyBehavior
{
public:
    FlyWithWings() : IFlyBehavior() {}

	void Fly() override
	{
		std::cout << "I'm flying with wings!!" << std::endl;
        m_flightCount++;
	}

    [[nodiscard]] int GetFlightCount() const override
    {
        return m_flightCount;
    }

    [[nodiscard]] bool CanFly() const override
    {
        return true;
    }

private:
    int m_flightCount = 0;
};