#pragma once

#include "IQuackBehavior.h"
#include <iostream>

class SqueakBehavior : public IQuackBehavior
{
public:
    SqueakBehavior() : IQuackBehavior()
    {
    }

    void Quack() override
    {
        std::cout << "Squeek!!!" << std::endl;
    }
};