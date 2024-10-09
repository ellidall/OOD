#pragma once

#include "IBeverage.h"

class CondimentDecorator : public IBeverage
{
public:
    [[nodiscard]] std::string GetDescription() const override
    {
        return m_beverage->GetDescription() + ", " + GetCondimentDescription();
    }

    [[nodiscard]] double GetCost() const override
    {
        return m_beverage->GetCost() + GetCondimentCost();
    }

    [[nodiscard]] virtual std::string GetCondimentDescription() const = 0;
    [[nodiscard]] virtual double GetCondimentCost() const = 0;
protected:
    explicit CondimentDecorator(IBeveragePtr&& beverage)
            : m_beverage(std::move(beverage))
    {
    }

private:
    IBeveragePtr m_beverage;
};

class Cinnamon : public CondimentDecorator
{
public:
    explicit Cinnamon(IBeveragePtr&& beverage)
            : CondimentDecorator(std::move(beverage))
    {}

protected:
    [[nodiscard]] double GetCondimentCost() const override
    {
        return 20;
    }

    [[nodiscard]] std::string GetCondimentDescription() const override
    {
        return "Cinnamon";
    }
};

class Lemon : public CondimentDecorator
{
public:
    explicit Lemon(IBeveragePtr&& beverage, unsigned quantity = 1)
            : CondimentDecorator(std::move(beverage)), m_quantity(quantity)
    {}

protected:
    [[nodiscard]] double GetCondimentCost() const override
    {
        return 10.0 * m_quantity;
    }

    [[nodiscard]] std::string GetCondimentDescription() const override
    {
        return "Lemon x " + std::to_string(m_quantity);
    }

private:
    unsigned m_quantity;
};

enum class IceCubeType
{
    DRY,
    WATER
};

class IceCubes : public CondimentDecorator
{
public:
    IceCubes(IBeveragePtr&& beverage, unsigned quantity, IceCubeType type = IceCubeType::WATER)
            : CondimentDecorator(std::move(beverage)), m_quantity(quantity), m_type(type)
    {}

protected:
    [[nodiscard]] double GetCondimentCost() const override
    {
        return (m_type == IceCubeType::DRY ? 10 : 5) * m_quantity;
    }

    [[nodiscard]] std::string GetCondimentDescription() const override
    {
        return std::string(m_type == IceCubeType::DRY ? "DRY" : "WATER")
               + " ice cubes x " + std::to_string(m_quantity);
    }

private:
    unsigned m_quantity;
    IceCubeType m_type;
};

enum class SyrupType
{
    CHOCOLATE,
    MAPLE,
};

class Syrup : public CondimentDecorator
{
public:
    Syrup(IBeveragePtr&& beverage, SyrupType syrupType)
            : CondimentDecorator(std::move(beverage)), m_syrupType(syrupType)
    {}

protected:
    [[nodiscard]] double GetCondimentCost() const override
    {
        return 15;
    }

    [[nodiscard]] std::string GetCondimentDescription() const override
    {
        return std::string(m_syrupType == SyrupType::CHOCOLATE ? "Chocolate" : "MAPLE")
               + " syrup";
    }

private:
    SyrupType m_syrupType;
};

class ChocolateCrumbs : public CondimentDecorator
{
public:
    ChocolateCrumbs(IBeveragePtr&& beverage, unsigned mass)
            : CondimentDecorator(std::move(beverage)), m_mass(mass)
    {
    }

    [[nodiscard]] double GetCondimentCost() const override
    {
        return 2.0 * m_mass;
    }

    [[nodiscard]] std::string GetCondimentDescription() const override
    {
        return "Chocolate crumbs " + std::to_string(m_mass) + "g";
    }

private:
    unsigned m_mass;
};

class CoconutFlakes : public CondimentDecorator
{
public:
    CoconutFlakes(IBeveragePtr&& beverage, unsigned mass)
            : CondimentDecorator(std::move(beverage)), m_mass(mass)
    {}

protected:
    [[nodiscard]] double GetCondimentCost() const override
    {
        return 1.0 * m_mass;
    }

    [[nodiscard]] std::string GetCondimentDescription() const override
    {
        return "Coconut flakes " + std::to_string(m_mass) + "g";
    }

private:
    unsigned m_mass;
};

class Cream : public CondimentDecorator
{
public:
    explicit Cream(IBeveragePtr&& beverage)
            : CondimentDecorator(std::move(beverage))
    {}

protected:
    [[nodiscard]] double GetCondimentCost() const override
    {
        return 25;
    }

    [[nodiscard]] std::string GetCondimentDescription() const override
    {
        return "Cream";
    }
};

class Chocolate : public CondimentDecorator
{
public:
    explicit Chocolate(IBeveragePtr&& beverage, unsigned slices = 1)
            : CondimentDecorator(std::move(beverage))
    {
        if (slices > MAX_SLICES)
        {
            throw std::invalid_argument("Error: max slices = " + std::to_string(MAX_SLICES));
        }

        m_slices = slices;
    }

protected:
    [[nodiscard]] double GetCondimentCost() const override
    {
        return m_slices * SLICE_COST;
    }

    [[nodiscard]] std::string GetCondimentDescription() const override
    {
        return "Chocolate x" + std::to_string(m_slices) + " slices";
    }

private:
    const unsigned SLICE_COST = 10;
    const unsigned MAX_SLICES = 5;

    unsigned m_slices;
};

enum class LiquorType
{
    CHOCOLATE,
    NUTTY
};

std::string GetStringLiquorType(LiquorType liqueurType)
{
    switch (liqueurType)
    {
        case LiquorType::CHOCOLATE:
            return "Chocolate";
        case LiquorType::NUTTY:
            return "Nutty";
        default:
            return "Unknown Liquor";
    }
}

class Liquor : public CondimentDecorator
{
public:
    Liquor(IBeveragePtr&& beverage, LiquorType type)
            : CondimentDecorator(std::move(beverage)), m_type(type)
    {}

protected:
    [[nodiscard]] double GetCondimentCost() const override
    {
        return 50;
    }

    [[nodiscard]] std::string GetCondimentDescription() const override
    {
        return GetStringLiquorType(m_type) + " Liquor";
    }

private:
    LiquorType m_type;
};