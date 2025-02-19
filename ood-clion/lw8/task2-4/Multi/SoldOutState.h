#pragma once

#include "IState.h"
#include "IMultiGumballMachine.h"

class SoldOutState : public IState
{
public:
    explicit SoldOutState(IMultiGumballMachine& gumballMachine) : m_gumballMachine(gumballMachine)
    {}

    void InsertQuarter() override
    {
        std::cout << "You can't insert a quarter, the machine is sold out\n";
    }

    void EjectQuarter() override
    {
        if (m_gumballMachine.GetQuarterCount() > 0)
        {
            m_gumballMachine.GiveOutAllQuarters();
        }
        else
        {
            std::cout << "You can't eject, you haven't inserted a quarter yet\n";
        }
    }

    void TurnCrank() override
    {
        std::cout << "You turned but there's no gumballs\n";
    }

    void Dispense() override
    {
        std::cout << "No gumball dispensed\n";
    }

    void FillBalls(unsigned numBalls) override
    {
        std::cout << "Added gumball\n";
        m_gumballMachine.FillBalls(numBalls);
        if (m_gumballMachine.GetBallCount() > 0)
        {
            if (m_gumballMachine.GetQuarterCount() > 0)
            {
                m_gumballMachine.SetHasQuarterState();
            }
            else
            {
                m_gumballMachine.SetNoQuarterState();
            }
        }
    }

    [[nodiscard]] std::string ToString() const override
    {
        return "sold out";
    }

private:
    IMultiGumballMachine& m_gumballMachine;
};