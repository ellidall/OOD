#pragma once

#include "IQuackBehavior.h"
#include <iostream>

class MuteQuackBehavior : public IQuackBehavior
{
public:
    MuteQuackBehavior() : IQuackBehavior(true)
    {}

    void Quack() override
    {
        std::cout << "I am in MUTE" << std::endl;
    }
};