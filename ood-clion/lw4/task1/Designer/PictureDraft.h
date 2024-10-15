#pragma once

#include <vector>
#include <memory>
#include "../ShapeFactory/Shape/Shape.h"

class PictureDraft
{
public:
    typedef std::vector<std::unique_ptr<Shape>> Shapes;

    void AddShape(std::unique_ptr<Shape>&& shape)
    {
        m_shapes.push_back(std::move(shape));
    }

    Shapes::iterator begin()
    {
        return m_shapes.begin();
    }

    Shapes::iterator end()
    {
        return m_shapes.end();
    }

    [[nodiscard]] Shapes::const_iterator begin() const
    {
        return m_shapes.begin();
    }

    [[nodiscard]] Shapes::const_iterator end() const
    {
        return m_shapes.end();
    }

private:
    Shapes m_shapes;
};