#pragma once

#include <string>
#include <cstdint>

namespace gfx
{
    class ICanvas
    {
    public:

        virtual ~ICanvas() = default;
        virtual void SetColor(uint32_t color) = 0;
        virtual void MoveTo(double x, double y) = 0;
        virtual void LineTo(double x, double y) = 0;
        virtual void DrawEllipse(double cx, double cy, double rx, double ry) = 0;
    };
}