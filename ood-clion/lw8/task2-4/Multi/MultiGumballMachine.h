#pragma once

#include <iostream>
#include <format>
#include "SoldState.h"
#include "SoldOutState.h"
#include "NoQuarterState.h"
#include "HasQuarterState.h"
#include "IMultiGumballMachine.h"

class MultiGumballMachine : private IMultiGumballMachine
{
public:
    explicit MultiGumballMachine(unsigned numBalls, unsigned maxQuarterCount = 5)
            : m_soldState(*this), m_soldOutState(*this), m_noQuarterState(*this), m_hasQuarterState(*this),
              m_state(&m_soldOutState), m_ballCount(numBalls), m_maxQuarterCount(maxQuarterCount)
    {
        if (m_ballCount > 0)
        {
            m_state = &m_noQuarterState;
        }
    }

    void EjectQuarter()
    {
        m_state->EjectQuarter();
    }

    void InsertQuarter()
    {
        m_state->InsertQuarter();
    }

    void TurnCrank()
    {
        m_state->TurnCrank();
        m_state->Dispense();
    }

    void Fill(unsigned numBalls)
    {
        m_state->FillBalls(numBalls);
    }

    [[nodiscard]] std::string ToString() const
    {
        return std::format(
                R"(Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: {} gumball{}, {} quarter{}
Machine is {})",
                m_ballCount,
                m_ballCount != 1 ? "s" : "",
                m_quarterCount,
                m_quarterCount != 1 ? "s" : "",
                m_state->ToString()
        );
    }

private:
    [[nodiscard]] unsigned GetBallCount() const override
    {
        return m_ballCount;
    }

    void ReleaseBall() override
    {
        if (m_ballCount != 0)
        {
            std::cout << "A gumball comes rolling out the slot...\n";
            --m_ballCount;
            --m_quarterCount;
        }
    }

    [[nodiscard]] unsigned GetQuarterCount() const override
    {
        return m_quarterCount;
    }

    [[nodiscard]] bool IsFull() const override
    {
        return m_quarterCount == m_maxQuarterCount;
    }

    void AddQuarter() override
    {
        ++m_quarterCount;
    }

    void FillBalls(unsigned numBalls) override
    {
        m_ballCount = numBalls;
    }

    void GiveOutAllQuarters() override
    {
        std::cout << "Give out all quarters\n";
        m_quarterCount = 0;
    }

    void SetSoldOutState() override
    {
        if (m_quarterCount != 0)
        {
            GiveOutAllQuarters();
        }
        m_state = &m_soldOutState;
    }

    void SetNoQuarterState() override
    {
        m_state = &m_noQuarterState;
    }

    void SetSoldState() override
    {
        m_state = &m_soldState;
    }

    void SetHasQuarterState() override
    {
        m_state = &m_hasQuarterState;
    }

private:
    const unsigned m_maxQuarterCount;
    unsigned m_ballCount = 0;
    unsigned m_quarterCount = 0;
    SoldState m_soldState;
    SoldOutState m_soldOutState;
    NoQuarterState m_noQuarterState;
    HasQuarterState m_hasQuarterState;
    IState* m_state;
};