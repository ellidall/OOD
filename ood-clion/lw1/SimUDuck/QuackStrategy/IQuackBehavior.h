#pragma once

class IQuackBehavior
{
public:
	virtual ~IQuackBehavior(){};
	virtual void Quack() = 0;
};