#pragma once

#include "IFlyBehavior.h"
#include <iostream>

class FlyNoWay : public IFlyBehavior
{
public:
    FlyNoWay() : IFlyBehavior(false) {}

    void Fly() override
    {
        std::cout << "I can't fly" << std::endl;
    }
};