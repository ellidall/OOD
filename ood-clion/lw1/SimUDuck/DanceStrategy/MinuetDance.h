#pragma once

#include "IDanceBehavior.h"
#include <iostream>

class MinuetDance : public IDanceBehavior
{
public:
	void Dance() override
	{
		std::cout << "I'm dance minuet!" << std::endl;
	}
};
