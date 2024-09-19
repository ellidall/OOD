#pragma once

#include "IQuackBehavior.h"
#include <iostream>

class MuteQuackBehavior : public IQuackBehavior
{
public:
	void Quack() override 
	{
		std::cout << "I am in MUTE" << std::endl;
	}
};