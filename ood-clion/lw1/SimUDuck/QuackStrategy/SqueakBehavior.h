#pragma once

#include "IQuackBehavior.h"
#include <iostream>

class SqueakBehavior : public IQuackBehavior
{
public:
	void Quack() override
	{
		std::cout << "Squeek!!!" << std::endl;
	}
};