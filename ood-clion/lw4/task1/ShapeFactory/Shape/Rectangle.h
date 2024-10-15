#pragma once

#include "Point.h"
#include "Color.h"
#include "Shape.h"

struct Rect
{
    Point leftTop;
    Point rightBottom;
};

class Rectangle : public Shape
{
public:
	Rectangle(const Color color, const Rect& bounds) : Shape(color), m_bounds(bounds)
	{
	}

	void Draw(ICanvas &canvas) const override
	{
		canvas.SetColor(GetColor());
		canvas.MoveTo(m_bounds.leftTop.x, m_bounds.leftTop.y);
		canvas.LineTo(m_bounds.rightBottom.x, m_bounds.leftTop.y);
		canvas.LineTo(m_bounds.rightBottom.x, m_bounds.rightBottom.y);
		canvas.LineTo(m_bounds.leftTop.x, m_bounds.rightBottom.y);
		canvas.LineTo(m_bounds.leftTop.x, m_bounds.leftTop.y);
	}

	[[nodiscard]] Point GetLeftTop() const
	{
		return m_bounds.leftTop;
	}

	[[nodiscard]] double GetWidth() const
	{
		return m_bounds.rightBottom.x - m_bounds.leftTop.x;
	}

	[[nodiscard]] double GetHeight() const
	{
		return m_bounds.rightBottom.y - m_bounds.leftTop.y;
	}

private:
	Rect m_bounds;
};