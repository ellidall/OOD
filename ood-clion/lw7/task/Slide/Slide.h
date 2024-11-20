#pragma once

#include "ISlide.h"
#include "../Shape/GroupShape.h"

class Slide : public ISlide
{
public:
    Slide(double width, double height, const std::shared_ptr<IGroupShape>& shapes)
            : m_width(width),
              m_height(height),
              m_shapes(shapes)
    {
    }

    [[nodiscard]] double GetWidth() const override
    {
        return m_width;
    }

    [[nodiscard]] double GetHeight() const override
    {
        return m_height;
    }

    [[nodiscard]] IShapes& GetShapes() override
    {
        return *m_shapes;
    }

    void Draw(gfx::ICanvas& canvas) const override
    {
        m_shapes->Draw(canvas);
    }

private:
    double m_width;
    double m_height;
    std::shared_ptr<IGroupShape> m_shapes;
};