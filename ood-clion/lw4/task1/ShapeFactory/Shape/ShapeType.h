#pragma once

enum class ShapeType
{
	ELLIPSE,
	RECTANGLE,
	REGULAR_POLYGON,
	TRIANGLE,
	LINE
};

inline std::string ShapeTypeToString(const ShapeType shape)
{
	switch (shape)
	{
		case ShapeType::ELLIPSE:
			return "ellipse";
		case ShapeType::RECTANGLE:
			return "rectangle";
		case ShapeType::REGULAR_POLYGON:
			return "regular_polygon";
		case ShapeType::TRIANGLE:
			return "triangle";
		case ShapeType::LINE:
			return "line";
		default:
			return "unknown";
	}
}