#pragma once

#include <iostream>
#include <functional>
#include "Strategies/FlyBehavior.h"
#include "Strategies/QuackBehavior.h"

using FlyBehavior = std::function<int()>;
using QuackBehavior = std::function<void()>;
using DanceBehavior = std::function<void()>;

class Duck
{
public:
    Duck(
            FlyBehavior flyBehavior,
            QuackBehavior quackBehavior,
            DanceBehavior danceBehavior
    ) : m_flyBehavior(std::move(flyBehavior)),
        m_quackBehavior(std::move(quackBehavior)),
        m_danceBehavior(std::move(danceBehavior))
    {}

    virtual ~Duck() = default;

    virtual void Display() const = 0;

    void Quack()
    {
        m_quackBehavior();
    }

    void Swim()
    {
        std::cout << "I'm swimming" << std::endl;
    }

    void Fly()
    {
        const int flightCount = m_flyBehavior();
        if (flightCount != 0 && flightCount % 2 == 0)
        {
            m_quackBehavior();
        }
//        m_flyBehavior.Fly();
//        if (m_flyBehavior.CanFly())
//        {
//            int flightCount = m_flyBehavior.GetFlightCount();
//            if (flightCount != 0 && flightCount % 2 == 0 && !m_quackBehavior.IsMute())
//            {
//                m_quackBehavior.Quack();
//            }
//        }
    }

    void Dance()
    {
        m_danceBehavior();
    }

    void SetFlyBehavior(FlyBehavior flyFunction)
    {
        m_flyBehavior = std::move(flyFunction);
    }

    void SetDanceBehavior(DanceBehavior danceFunction)
    {
        m_danceBehavior = std::move(danceFunction);
    }

    void SetQuackBehavior(QuackBehavior quackFunction)
    {
        m_quackBehavior = std::move(quackFunction);
    }

private:
    FlyBehavior m_flyBehavior;
    QuackBehavior m_quackBehavior;
    DanceBehavior m_danceBehavior;
};