#pragma once

#include "IDanceBehavior.h"
#include <iostream>

class WaltzDance : public IDanceBehavior
{
public:
	void Dance() override
	{
		std::cout << "I'm dance waltz!" << std::endl;
	}
};
