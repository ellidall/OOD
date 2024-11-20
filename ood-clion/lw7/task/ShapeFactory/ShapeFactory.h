#pragma once

#include "IShapeFactory.h"
#include "../Shape/Rectangle.h"
#include "../Shape/Ellipse.h"
#include "../Shape/Triangle.h"
#include "../Shape/Style/Style.h"

class ShapeFactory : public IShapeFactory
{
public:
    std::shared_ptr<IShape> CreateShape(const std::string& description) override
    {
        std::istringstream iss(description);
        std::string shapeType;
        iss >> shapeType;

        auto outlineStyle = ParseStyle(iss);
        auto fillStyle = ParseStyle(iss);

        if (shapeType == "triangle")
        {
            return ShapeFactory::CreateTriangle(iss, std::move(outlineStyle), std::move(fillStyle));
        }
        else if (shapeType == "ellipse")
        {
            return ShapeFactory::CreateEllipse(iss, std::move(outlineStyle), std::move(fillStyle));
        }
        else if (shapeType == "rectangle")
        {
            return ShapeFactory::CreateRectangle(iss, std::move(outlineStyle), std::move(fillStyle));
        }

        throw std::invalid_argument("Unknown shape type");
    }

private:
    static std::shared_ptr<Triangle> CreateTriangle(
            std::istringstream& iss,
            std::unique_ptr<IStyle> outlineStyle,
            std::unique_ptr<IStyle> fillStyle
    )
    {
        const auto rect = ParseRect(iss);
        return std::make_unique<Triangle>(rect, std::move(outlineStyle), std::move(fillStyle));
    }

    static std::shared_ptr<Ellipse> CreateEllipse(
            std::istringstream& iss,
            std::unique_ptr<IStyle> outlineStyle,
            std::unique_ptr<IStyle> fillStyle
    )
    {
        const auto rect = ParseRect(iss);
        return std::make_unique<Ellipse>(rect, std::move(outlineStyle), std::move(fillStyle));
    }

    static std::shared_ptr<Rectangle> CreateRectangle(
            std::istringstream& iss,
            std::unique_ptr<IStyle> outlineStyle,
            std::unique_ptr<IStyle> fillStyle
    )
    {
        const auto rect = ParseRect(iss);
        return std::make_unique<Rectangle>(rect, std::move(outlineStyle), std::move(fillStyle));
    }

    static std::unique_ptr<IStyle> ParseStyle(std::istringstream& iss)
    {
        std::string colorStr;
        RGBAColor color;

        if (!(iss >> colorStr) || !ParseColor(colorStr, color))
        {
            return std::make_unique<Style>(std::nullopt);
        }

        auto style = std::make_unique<Style>(color);
        style->Enable(true);

        return style;
    }

    static bool ParseColor(std::string colorStr, RGBAColor& color)
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

    static RectD ParseRect(std::istringstream& iss)
    {
        double left, top, width, height;

        if (!(iss >> left >> top >> width >> height))
        {
            throw std::invalid_argument("Invalid rect parameters");
        }
        if (width < 0 || height < 0)
        {
            throw std::invalid_argument("Width and height must be non-negative");
        }

        return {left, top, width, height};
    }
};
