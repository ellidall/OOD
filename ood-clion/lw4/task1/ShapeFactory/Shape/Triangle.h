#pragma once

#include <iostream>
#include <string>
#include "Point.h"
#include "Color.h"
#include "Shape.h"

class Triangle : public Shape
{
public:
	Triangle(
		const Color color,
		const Point firstAngle,
		const Point secondAngle,
		const Point thirdAngle
	): Shape(color),
	   m_firstAngle(firstAngle),
	   m_secondAngle(secondAngle),
	   m_thirdAngle(thirdAngle)
	{
	}

	void Draw(gfx::ICanvas &canvas) const override
	{
		canvas.SetColor(GetColor());
		canvas.MoveTo(m_firstAngle.x, m_firstAngle.y);
		canvas.LineTo(m_secondAngle.x, m_secondAngle.y);
		canvas.LineTo(m_thirdAngle.x, m_thirdAngle.y);
		canvas.LineTo(m_firstAngle.x, m_firstAngle.y);
	}

	[[nodiscard]] Point GetFirstAngle() const
	{
		return m_firstAngle;
	}

	[[nodiscard]] Point GetSecondAngle() const
	{
		return m_secondAngle;
	}

	[[nodiscard]] Point GetThirdAngle() const
	{
		return m_thirdAngle;
	}

private:
	Point m_firstAngle;
	Point m_secondAngle;
	Point m_thirdAngle;
};