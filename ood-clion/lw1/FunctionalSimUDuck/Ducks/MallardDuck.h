#pragma once

#include "../Duck.h"
#include "../Strategies/FlyBehavior.h"
#include "../Strategies/QuackBehavior.h"
#include "../Strategies/DanceBehavior.h"
#include <iostream>

class MallardDuck : public Duck
{
public:
    MallardDuck() : Duck(
            FlyWithWings(),
            SimpleQuack(),
            WaltzDance()
    )
    {}

    void Display() const override
    {
        std::cout << "I'm mallard duck" << std::endl;
    }
};