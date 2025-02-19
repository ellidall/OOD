#pragma once

#include <format>
#include <iostream>

class NaiveGumballMachine
{
public:
    enum class State
    {
        SoldOut,
        NoQuarter,
        HasQuarter,
        Sold,
    };

    explicit NaiveGumballMachine(unsigned count)
            : m_ballCount(count), m_state(count > 0 ? State::NoQuarter : State::SoldOut)
    {}

    void InsertQuarter()
    {
        if (m_quarterCount < m_maxQuarterCount)
        {
            switch (m_state)
            {
                case State::SoldOut:
                    std::cout << "You can't insert a quarter, the machine is sold out\n";
                    break;
                case State::NoQuarter:
                    std::cout << "You inserted a quarter\n";
                    m_quarterCount++;
                    m_state = State::HasQuarter;
                    break;
                case State::HasQuarter:
                    std::cout << "You inserted another quarter\n";
                    m_quarterCount++;
                    break;
                case State::Sold:
                    std::cout << "Please wait, we're already giving you a gumball\n";
                    break;
            }
        }
        else
        {
            std::cout << "You can't insert another quarter\n";
        }
    }

    void EjectQuarter()
    {
        switch (m_state)
        {
            case State::SoldOut:
                if (m_quarterCount > 0)
                {
                    std::cout << "Return all quarters\n";
                    m_quarterCount = 0;
                }
                else
                {
                    std::cout << "You can't eject, you haven't inserted a quarter yet\n";
                }
                break;
            case State::NoQuarter:
                std::cout << "You can't eject, you haven't inserted a quarter yet\n";
                break;
            case State::HasQuarter:
                std::cout << "Return all quarters\n";
                m_quarterCount = 0;
                m_state = State::NoQuarter;
                break;
            case State::Sold:
                std::cout << "Sorry you already turned the crank\n";
                break;
        }
    }

    void TurnCrank()
    {
        switch (m_state)
        {
            case State::SoldOut:
                std::cout << "You turned but there's no gumballs\n";
                break;
            case State::NoQuarter:
                std::cout << "You turned but there's no quarter\n";
                break;
            case State::HasQuarter:
                if (m_ballCount <= 0)
                {
                    std::cout << "No quarters left\n";
                    m_state = State::NoQuarter;
                }
                else
                {
                    std::cout << "You turned...\n";
                    m_state = State::Sold;
                    Dispense();
                }
                break;
            case State::Sold:
                std::cout << "Turning twice doesn't get you another gumball\n";
                break;
        }
    }

    void Refill(unsigned numBalls)
    {
        switch (m_state)
        {
            case State::SoldOut:
                m_ballCount = numBalls;
                std::cout << "Added gumball\n";
                if (m_ballCount > 0)
                {
                    if (m_quarterCount > 0)
                    {
                        m_state = State::HasQuarter;
                    }
                    else
                    {
                        m_state = State::NoQuarter;
                    }
                }
                break;
            case State::NoQuarter:
            case State::HasQuarter:
                m_ballCount = numBalls;
                std::cout << "Gumballs added\n";
                break;
            case State::Sold:
                std::cout << "Can't add gumball when giving gumball\n";
                break;
        }

    }

    [[nodiscard]] std::string ToString() const
    {
        std::string state;
        if (m_state == State::SoldOut) state = "sold out";
        else if (m_state == State::NoQuarter) state = "waiting for quarter";
        else if (m_state == State::HasQuarter) state = "waiting for turn of crank";
        else state = "delivering a gumball";

        return std::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: {} gumball{}
Machine is {}
)",
                m_ballCount, m_ballCount != 1 ? "s" : "", state);
    }

private:
    void Dispense()
    {
        if (m_ballCount > 0 && m_quarterCount > 0)
        {
            --m_ballCount;
            --m_quarterCount;

            std::cout << "A gumball comes rolling out the slot...\n";

            if (m_ballCount == 0)
            {
                std::cout << "Oops, out of gumballs\n";
                m_quarterCount = 0;
                m_state = State::SoldOut;
            }
            else if (m_quarterCount > 0)
            {
                m_state = State::HasQuarter;
            }
        }
    }

    unsigned m_ballCount;
    unsigned m_quarterCount = 0;
    const unsigned m_maxQuarterCount = 5;
    State m_state = State::SoldOut;
};