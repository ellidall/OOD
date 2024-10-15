#pragma once

#include <iostream>
#include <string>
#include "Point.h"
#include "Color.h"
#include "Shape.h"

class Line : public Shape
{
public:
	Line(
		const Color color,
		const Point start,
		const Point end
	) : Shape(color), m_start(start), m_end(end)
	{
	}

	void Draw(ICanvas &canvas) const override
	{
		canvas.SetColor(GetColor());
		canvas.MoveTo(m_start.x, m_start.y);
		canvas.LineTo(m_end.x, m_end.y);
	}

	[[nodiscard]] Point GetStartPoint() const
	{
		return m_start;
	}

	[[nodiscard]] Point GetEndPoint() const
	{
		return m_end;
	}

private:
	Point m_start;
	Point m_end;
};