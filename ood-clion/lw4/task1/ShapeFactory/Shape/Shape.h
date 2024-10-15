#pragma once

#include "../../Canvas/ICanvas.h"
#include "Color.h"

class Shape
{
public:
	explicit Shape(const Color color): m_color(color)
	{}

	virtual void Draw(ICanvas &canvas) const = 0;

	[[nodiscard]] Color GetColor() const
	{
		return m_color;
	}

	virtual ~Shape() = default;

private:
	Color m_color;
};