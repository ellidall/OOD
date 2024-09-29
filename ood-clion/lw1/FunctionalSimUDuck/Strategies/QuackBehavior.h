#pragma once

#include <iostream>
#include <functional>

//struct QuackBehavior
//{
//    std::function<void()> Quack;
//    std::function<bool()> IsMute;
//};
//
//std::function<QuackBehavior()> MuteQuack()
//{
//    const bool isMute = true;
//
//    QuackBehavior quackBehavior;
//    quackBehavior.Quack = []() {
//        std::cout << "I am in MUTE" << std::endl;
//    };
//    quackBehavior.IsMute = []() { return isMute; };
//
//    return [quackBehavior]() { return quackBehavior; };
//}
//
//std::function<QuackBehavior()> Squeak()
//{
//    const bool isMute = false;
//
//    QuackBehavior quackBehavior;
//    quackBehavior.Quack = []() {
//        std::cout << "Squeek!!!" << std::endl;
//    };
//    quackBehavior.IsMute = []() { return isMute; };
//
//    return [quackBehavior]() { return quackBehavior; };
//}
//
//std::function<QuackBehavior()> SimpleQuack()
//{
//    const bool isMute = false;
//
//    QuackBehavior quackBehavior;
//    quackBehavior.Quack = []() {
//        std::cout << "Quack Quack!!!" << std::endl;
//    };
//    quackBehavior.IsMute = []() { return isMute; };
//
//    return [quackBehavior]() { return quackBehavior; };
//}

std::function<void()> SimpleQuack()
{
    return []() {
        std::cout << "Quack Quack!!!" << std::endl;
    };
}

std::function<void()> Squeak()
{
    return []() {
        std::cout << "Squeek!!!" << std::endl;
    };
}

std::function<void()> MuteQuack()
{
    return []() {};
}