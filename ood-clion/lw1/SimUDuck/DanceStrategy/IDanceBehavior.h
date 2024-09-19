#pragma once

class IDanceBehavior
{
public:
	virtual ~IDanceBehavior(){};
	virtual void Dance() = 0;
};