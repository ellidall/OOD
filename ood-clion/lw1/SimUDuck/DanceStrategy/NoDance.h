#pragma once

#include "IDanceBehavior.h"
#include <iostream>

class NoDance : public IDanceBehavior
{
public:
	void Dance() override
	{
		std::cout << "I can't dance :(" << std::endl;
	}
};
