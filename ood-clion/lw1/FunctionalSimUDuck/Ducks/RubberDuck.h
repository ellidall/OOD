#pragma once

#include "../Duck.h"
#include "../Strategies/FlyBehavior.h"
#include "../Strategies/QuackBehavior.h"
#include "../Strategies/DanceBehavior.h"
#include <iostream>

class RubberDuck : public Duck
{
public:
    RubberDuck() : Duck(
            FlyNoWay(),
            Squeak(),
            NoDance()
    )
    {}

    void Display() const override
    {
        std::cout << "I'm rubber duck" << std::endl;
    }
};