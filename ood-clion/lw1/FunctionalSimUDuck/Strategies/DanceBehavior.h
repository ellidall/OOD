#pragma once

#include <iostream>
#include <functional>

std::function<void()> MinuetDance()
{
    return []() {
        std::cout << "I'm dance minuet!" << std::endl;
    };
}

std::function<void()> NoDance()
{
    return []() {
        std::cout << "I can't dance :(" << std::endl;
    };
}

std::function<void()> WaltzDance()
{
    return []() {
        std::cout << "I'm dance waltz!" << std::endl;
    };
}