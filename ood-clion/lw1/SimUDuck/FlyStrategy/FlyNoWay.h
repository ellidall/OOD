#pragma once

#include "IFlyBehavior.h"
#include <iostream>

class FlyNoWay : public IFlyBehavior
{
public:
    FlyNoWay() : IFlyBehavior()
    {
    }

    void Fly() override
    {
        std::cout << "I can't fly" << std::endl;
    }

    [[nodiscard]] int GetFlightCount() const override
    {
        return 0;
    }

    [[nodiscard]] bool CanFly() const override
    {
        return false;
    }
};