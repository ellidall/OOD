#pragma once

#include "IQuackBehavior.h"
#include <iostream>

class QuackBehavior : public IQuackBehavior
{
public:
    QuackBehavior() : IQuackBehavior()
    {
    }

	void Quack() override
	{
		std::cout << "Quack Quack!!!" << std::endl;
	}
};