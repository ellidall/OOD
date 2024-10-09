#pragma once

#include <string>
#include <memory>

class IBeverage
{
public:
    [[nodiscard]] virtual std::string GetDescription() const = 0;
    [[nodiscard]] virtual double GetCost() const = 0;
    virtual ~IBeverage() = default;
};

typedef std::unique_ptr<IBeverage> IBeveragePtr;