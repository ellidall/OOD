#pragma once

#include <memory>
#include <algorithm>
#include <sstream>
#include "IShapeFactory.h"
#include "Shape/Triangle.h"
#include "Shape/Ellipse.h"
#include "Shape/Rectangle.h"
#include "Shape/RegularPolygon.h"
#include "Shape/ShapeType.h"
#include "Shape/Line.h"

class ShapeFactory : public IShapeFactory
{
public:
    std::unique_ptr<Shape> CreateShape(const std::string& description) override
    {
        std::istringstream iss(description);
        std::string colorStr, type;
        Color color;

        iss >> colorStr >> type;
        if (colorStr.empty() || type.empty())
        {
            throw std::invalid_argument("Insufficient arguments for shape");
        }

        if (!ParseColor(colorStr, color))
        {
            throw std::invalid_argument("Invalid color format");
        }

        if (type == ShapeTypeToString(ShapeType::TRIANGLE))
        {
            return CreateTriangle(color, iss);
        }
        if (type == ShapeTypeToString(ShapeType::ELLIPSE))
        {
            return CreateEllipse(color, iss);
        }
        if (type == ShapeTypeToString(ShapeType::RECTANGLE))
        {
            return CreateRectangle(color, iss);
        }
        if (type == ShapeTypeToString(ShapeType::REGULAR_POLYGON))
        {
            return CreateRegularPolygon(color, iss);
        }
        if (type == ShapeTypeToString(ShapeType::LINE))
        {
            return CreateLine(color, iss);
        }

        throw std::invalid_argument("Unknown shape");
    }

private:
    static bool ParseColor(std::string colorStr, Color& color)
    {
        if (colorStr.size() != 7 || colorStr[0] != '#')
        {
            return false;
        }
        std::stringstream ss;
        ss << std::hex << colorStr.append("FF").substr(1);

        if (!(ss >> color))
        {
            return false;
        }

        return ss.eof();
    }

    static std::unique_ptr<Triangle> CreateTriangle(Color color, std::istringstream& iss)
    {
        double x1, y1, x2, y2, x3, y3;
        if (!(iss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3))
        {
            throw std::invalid_argument("Invalid parameters for triangle");
        }

        return std::move(std::make_unique<Triangle>(
                color,
                Point(x1, y1), Point(x2, y2), Point(x3, y3)
        ));
    }

    static std::unique_ptr<Ellipse> CreateEllipse(Color color, std::istringstream& iss)
    {
        double centerX, centerY, horizontalRadius, verticalRadius;
        if (!(iss >> centerX >> centerY >> horizontalRadius >> verticalRadius))
        {
            throw std::invalid_argument("Invalid parameters for circle");
        }
        if (horizontalRadius < 0 || verticalRadius < 0)
        {
            throw std::invalid_argument("Radius must be non-negative for circle");
        }

        return std::move(std::make_unique<Ellipse>(color, Point(centerX, centerY), horizontalRadius, verticalRadius));
    }

    static std::unique_ptr<Rectangle> CreateRectangle(Color color, std::istringstream& iss)
    {
        double leftTopX, leftTopY, width, height;
        if (!(iss >> leftTopX >> leftTopY >> width >> height))
        {
            throw std::invalid_argument("Invalid parameters for rectangle");
        }
        if (width < 0 || height < 0)
        {
            throw std::invalid_argument("Width and height must be non-negative for rectangle");
        }

        return std::move(std::make_unique<Rectangle>(
                color, Rect(Point(leftTopX, leftTopY), Point(leftTopX + width, leftTopY + height))
        ));
    }

    static std::unique_ptr<RegularPolygon> CreateRegularPolygon(Color color, std::istringstream& iss)
    {
        unsigned pointsCount;
        double centerX, centerY, radius;
        if (!(iss >> centerX >> centerY >> pointsCount >> radius))
        {
            throw std::invalid_argument("Invalid parameters for regular polygon");
        }
        if (radius < 0)
        {
            throw std::invalid_argument("Radius must be non-negative for regular polygon");
        }

        return std::move(std::make_unique<RegularPolygon>(
                color, Point(centerX, centerY), pointsCount, radius
        ));
    }

    static std::unique_ptr<Line> CreateLine(Color color, std::istringstream& iss)
    {
        double x1, y1, x2, y2;
        if (!(iss >> x1 >> y1 >> x2 >> y2))
        {
            throw std::invalid_argument("Invalid parameters for line");
        }

        return std::move(std::make_unique<Line>(
                color,
                Point(x1, y1), Point(x2, y2)
        ));
    }
};
