#pragma once

#include "Canvas/ICanvas.h"

class IDrawable
{
public:
    virtual void Draw(gfx::ICanvas& canvas) const = 0;
    virtual ~IDrawable() = default;
};