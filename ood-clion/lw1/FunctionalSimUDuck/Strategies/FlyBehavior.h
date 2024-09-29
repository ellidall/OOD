#pragma once

#include <iostream>
#include <functional>

//struct FlyBehavior
//{
//    std::function<void()> Fly;
//    std::function<int()> GetFlightCount;
//    std::function<bool()> CanFly;
//    int flightCount = 0;
//};
//
//FlyBehavior FlyWithWings() {
//    const bool canFly = true;
//
//    FlyBehavior flyBehavior;
//    flyBehavior.Fly = [&flyBehavior]() {
//        flyBehavior.flightCount++;
//        std::cout << "I'm flying with wings!!" << std::endl;
//    };
//    flyBehavior.GetFlightCount = [&flyBehavior]() { return flyBehavior.flightCount; };
//    flyBehavior.CanFly = []() { return canFly; };
//
//    return flyBehavior;
//}
//
//FlyBehavior FlyNoWay()
//{
//    const bool canFly = false;
//
//    FlyBehavior flyBehavior;
//    flyBehavior.Fly = []() {
//        std::cout << "I can't fly" << std::endl;
//    };
//    flyBehavior.GetFlightCount = [&flyBehavior]() { return flyBehavior.flightCount; };
//    flyBehavior.CanFly = []() { return canFly; };
//
//    return flyBehavior;
//}

std::function<int()> FlyWithWings()
{
    int flightCount = 0;
    return [flightCount]() mutable {
        flightCount++;
        std::cout << "I'm flying with wings!! FlightCount: " << flightCount << std::endl;
        return flightCount;
    };
}

std::function<int()> FlyNoWay()
{
    return []() {
        std::cout << "I can't fly" << std::endl;
        return 0;
    };
}