#pragma once

struct IMultiGumballMachine
{
    virtual void ReleaseBall() = 0;
    [[nodiscard]] virtual unsigned GetBallCount() const = 0;
    [[nodiscard]] virtual unsigned GetQuarterCount() const = 0;
    [[nodiscard]] virtual bool IsFull() const = 0;
    virtual void AddQuarter() = 0;
    virtual void FillBalls(unsigned numBalls) = 0;
    virtual void GiveOutAllQuarters() = 0;

    virtual void SetSoldOutState() = 0;
    virtual void SetNoQuarterState() = 0;
    virtual void SetSoldState() = 0;
    virtual void SetHasQuarterState() = 0;

    virtual ~IMultiGumballMachine() = default;
};