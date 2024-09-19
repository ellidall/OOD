#pragma once

class IFlyBehavior
{
public:
	virtual ~IFlyBehavior(){};
	virtual void Fly() = 0;
};