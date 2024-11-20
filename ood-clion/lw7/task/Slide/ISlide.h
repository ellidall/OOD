#pragma once

#include "../IDrawable.h"
#include "../Shape/IShapes.h"

class ISlide : public IDrawable
{
public:
    [[nodiscard]] virtual double GetWidth() const = 0;
    [[nodiscard]] virtual double GetHeight() const = 0;
    [[nodiscard]] virtual IShapes& GetShapes() = 0;
    ~ISlide() override = default;
};