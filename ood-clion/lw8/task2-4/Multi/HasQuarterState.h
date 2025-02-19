#pragma once

#include "IState.h"
#include "IMultiGumballMachine.h"

class HasQuarterState : public IState
{
public:
    explicit HasQuarterState(IMultiGumballMachine& gumballMachine) : m_gumballMachine(gumballMachine)
    {}

    void InsertQuarter() override
    {
        if (!m_gumballMachine.IsFull())
        {
            m_gumballMachine.AddQuarter();
            std::cout << "You inserted another quarter\n";
        }
        else
        {
            std::cout << "You can't insert another quarter\n";
        }
    }

    void EjectQuarter() override
    {
        m_gumballMachine.GiveOutAllQuarters();
        m_gumballMachine.SetNoQuarterState();
    }

    void TurnCrank() override
    {
        if (m_gumballMachine.GetQuarterCount() <= 0)
        {
            std::cout << "No quarters left\n";
            m_gumballMachine.SetNoQuarterState();
        }
        else
        {
            std::cout << "You turned...\n";
            m_gumballMachine.SetSoldState();
        }
    }

    void Dispense() override
    {
        std::cout << "No gumball dispensed\n";
    }

    void FillBalls(unsigned numBalls) override
    {
        std::cout << "Gumballs added\n";
        m_gumballMachine.FillBalls(numBalls);
    }

    [[nodiscard]] std::string ToString() const override
    {
        return "waiting for turn of crank";
    }

private:
    IMultiGumballMachine& m_gumballMachine;
};