#pragma once

#include <iostream>
#include <functional>

struct FlyBehavior
{
    std::function<void()> FlyWithWings;
    std::function<int()> GetFlightCount;
};

FlyBehavior MakeFlyBehavior()
{
    int flyCount;
    FlyBehavior flyBehavior;

    flyBehavior.FlyWithWings = [&flyCount]() {
        flyCount++;
        std::cout << "I'm flying with wings!!" << std::endl;
    };

    flyBehavior.GetFlightCount = [&flyCount]() { return flyCount; };

    return  flyBehavior;
}

void FlyNoWay()
{
    std::cout << "I can't fly" << std::endl;
}