#pragma once

#include "IQuackBehavior.h"
#include <iostream>

class MuteQuackBehavior : public IQuackBehavior
{
public:
    MuteQuackBehavior() : IQuackBehavior()
    {
    }

    void Quack() override
    {
    }
};