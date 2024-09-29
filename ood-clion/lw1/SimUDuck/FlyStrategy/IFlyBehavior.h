#pragma once

class IFlyBehavior
{
public:
    virtual ~IFlyBehavior() = default;
    virtual void Fly() = 0;
    [[nodiscard]] virtual int GetFlightCount() const = 0;
    [[nodiscard]] virtual bool CanFly() const = 0;
};