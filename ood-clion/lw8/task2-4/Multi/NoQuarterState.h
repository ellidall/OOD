#pragma once

#include "IState.h"
#include "IMultiGumballMachine.h"

class NoQuarterState : public IState
{
public:
    explicit NoQuarterState(IMultiGumballMachine& gumballMachine) : m_gumballMachine(gumballMachine)
    {}

    void InsertQuarter() override
    {
        std::cout << "You inserted a quarter\n";
        m_gumballMachine.AddQuarter();
        m_gumballMachine.SetHasQuarterState();
    }

    void EjectQuarter() override
    {
        std::cout << "You haven't inserted a quarter\n";
    }

    void TurnCrank() override
    {
        std::cout << "You turned but there's no quarter\n";
    }

    void Dispense() override
    {
        std::cout << "You need to pay first\n";
    }

    void FillBalls(unsigned numBalls) override
    {
        std::cout << "Gumballs added\n";
        m_gumballMachine.FillBalls(numBalls);
    }

    [[nodiscard]] std::string ToString() const override
    {
        return "waiting for quarter";
    }

private:
    IMultiGumballMachine& m_gumballMachine;
};