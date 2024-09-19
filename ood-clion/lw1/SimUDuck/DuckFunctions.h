#pragma once

#include "Duck.h"

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck)
{
	std::cout << "---------------" << std::endl;
	DrawDuck(duck);
	duck.Swim();
	duck.Quack();
	duck.Fly();
	duck.Dance();
	std::cout << "---------------" << std::endl	<< std::endl;
}