#pragma once

#include "Point.h"
#include "Color.h"
#include "Shape.h"

class Ellipse : public Shape
{
public:
    Ellipse(
            const Color color,
            const Point center,
            const double horizontalRadius,
            const double verticalRadius
    ) : Shape(color),
        m_center(center),
        m_horizontalRadius(horizontalRadius),
        m_verticalRadius(verticalRadius)
    {
    }

    void Draw(gfx::ICanvas& canvas) const override
    {
        canvas.SetColor(GetColor());
        canvas.DrawEllipse(m_center.x, m_center.y, m_horizontalRadius, m_verticalRadius);
    }

    [[nodiscard]] Point GetCenter() const
    {
        return m_center;
    }

    [[nodiscard]] double GetHorizontalRadius() const
    {
        return m_horizontalRadius;
    }

    [[nodiscard]] double GetVerticalRadius() const
    {
        return m_verticalRadius;
    }

private:
    Point m_center;
    double m_horizontalRadius;
    double m_verticalRadius;
};