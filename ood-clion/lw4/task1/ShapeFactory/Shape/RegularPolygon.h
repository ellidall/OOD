#pragma once

#include "Point.h"
#include "Color.h"
#include "Shape.h"
#include <cmath>

class RegularPolygon : public Shape
{
public:
	RegularPolygon(
		const Color color,
		const Point center,
		const unsigned pointsCount,
		const double radius
	): Shape(color),
	   m_center(center),
	   m_pointsCount(pointsCount),
	   m_radius(radius)
	{
	}

	void Draw(ICanvas &canvas) const override
	{
		canvas.SetColor(GetColor());

		const double angleStep = 2 * M_PI / m_pointsCount;

		const double startX = m_center.x + m_radius * std::cos(0);
		const double startY = m_center.y + m_radius * std::sin(0);

		double prevX = startX;
		double prevY = startY;

		for (int i = 1; i <= m_pointsCount; ++i)
		{
			const double angle = i * angleStep;
			const double x = m_center.x + m_radius * std::cos(angle);
			const double y = m_center.y + m_radius * std::sin(angle);

			canvas.MoveTo(prevX, prevY);
			canvas.LineTo(x, y);

			prevX = x;
			prevY = y;
		}

		canvas.MoveTo(prevX, prevY);
		canvas.LineTo(startX, startY);
	}

	[[nodiscard]] Point GetCenter() const
	{
		return m_center;
	}

	[[nodiscard]] unsigned GetPointsCount() const
	{
		return m_pointsCount;
	}

	[[nodiscard]] double GetRadius() const
	{
		return m_radius;
	}

private:
	Point m_center;
	unsigned m_pointsCount;
	double m_radius;
};
