#include <iostream>
#include "Beverages.h"
#include "Condiments.h"

int main()
{
    Latte latte(Portion::STANDARD);
    std::cout << latte.GetDescription() << ": " << latte.GetCost() << std::endl;

    Milkshake milkshake1(MilkshakeSize::SMALL);
    Milkshake milkshake2(MilkshakeSize::MEDIUM);
    Milkshake milkshake3(MilkshakeSize::LARGE);
    std::cout << milkshake1.GetDescription() << ": " << milkshake1.GetCost() << std::endl;
    std::cout << milkshake2.GetDescription() << ": " << milkshake2.GetCost() << std::endl;
    std::cout << milkshake3.GetDescription() << ": " << milkshake3.GetCost() << std::endl;

    auto cappuccino = std::make_unique<Cappuccino>(Portion::STANDARD);
    auto cappuccinoWithLiquor = std::make_unique<Liquor>(std::move(cappuccino), LiquorType::NUTTY);
    std::cout << cappuccinoWithLiquor->GetDescription() << ": " << cappuccinoWithLiquor->GetCost() << std::endl;

    return EXIT_SUCCESS;
}
