#pragma once

#include <utility>

#include "IBeverage.h"

class Beverage : public IBeverage
{
public:
    explicit Beverage(std::string description) : m_description(std::move(description))
    {}

    [[nodiscard]] std::string GetDescription() const override
    {
        return m_description;
    }

private:
    std::string m_description;
};

enum class Portion
{
    STANDARD,
    DOUBLE,
};

std::string GetStringPortion(Portion portion)
{
    switch (portion)
    {
        case Portion::STANDARD:
            return "Standard";
        case Portion::DOUBLE:
            return "Double";
        default:
            return "Unknown Portion";
    }
}

class Coffee : public Beverage
{
public:
    explicit Coffee(Portion portion, const std::string& description = "Coffee") : Beverage(description),
                                                                                  m_portion(portion)
    {}

    [[nodiscard]] double GetCost() const override
    {
        return 60;
    }

protected:
    Portion m_portion;
};

class Cappuccino : public Coffee
{
public:
    explicit Cappuccino(Portion portion) : Coffee(portion, GetStringPortion(portion) + "Cappuccino")
    {}

    [[nodiscard]] double GetCost() const override
    {
        return m_portion == Portion::STANDARD ? 80 : 120;
    }
};

class Latte : public Coffee
{
public:
    explicit Latte(Portion portion) : Coffee(portion, "Latte")
    {}

    [[nodiscard]] double GetCost() const override
    {
        return m_portion == Portion::STANDARD ? 90 : 130;
    }
};

enum class TeaType
{
    WHITE,
    BLACK,
    GREEN,
    RED,
};

std::string GetStringTeaType(TeaType teaType)
{
    switch (teaType)
    {
        case TeaType::WHITE:
            return "White";
        case TeaType::BLACK:
            return "Black";
        case TeaType::GREEN:
            return "Green";
        case TeaType::RED:
            return "Red";
        default:
            return "Unknown Tea Type";
    }
}

class Tea : public Beverage
{
public:
    explicit Tea(TeaType teaType)
            : Beverage(GetStringTeaType(teaType) + " Tea")
    {}

    [[nodiscard]] double GetCost() const override
    {
        return 30;
    }
};

enum class MilkshakeSize
{
    SMALL,
    MEDIUM,
    LARGE,
};

std::string GetStringMilkshakeSize(MilkshakeSize size)
{
    switch (size)
    {
        case MilkshakeSize::SMALL:
            return "Small";
        case MilkshakeSize::MEDIUM:
            return "Medium";
        case MilkshakeSize::LARGE:
            return "Large";
        default:
            return "Unknown Size Type";
    }
}

class Milkshake : public Beverage
{
public:
    explicit Milkshake(MilkshakeSize size)
            : Beverage(GetStringMilkshakeSize(size) + " Milkshake"), m_size(size)
    {}

    [[nodiscard]] double GetCost() const override
    {
        switch (m_size)
        {
            case MilkshakeSize::SMALL:
                return 50;
            case MilkshakeSize::MEDIUM:
                return 60;
            case MilkshakeSize::LARGE:
                return 80;
        }
    }

private:
    MilkshakeSize m_size;
};
