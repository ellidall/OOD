#pragma once

class IFlyBehavior
{
public:
    explicit IFlyBehavior(bool canFly) : m_canFly(canFly)
    {}

    virtual ~IFlyBehavior() = default;
    virtual void Fly() = 0;

    [[nodiscard]] int GetFlightCount() const
    {
        return m_flightCount;
    }

    [[nodiscard]] bool CanFly() const
    {
        return m_canFly;
    }

protected:
    int m_flightCount = 0;
private:
    bool m_canFly;
};