#pragma once

#include "IShape.h"
#include "Shape.h"

class Triangle : public Shape
{
public:
    Triangle(const RectD& frame, std::unique_ptr<IStyle> outlineStyle, std::unique_ptr<IStyle> fillStyle)
            : Shape(frame, std::move(outlineStyle), std::move(fillStyle))
    {
    }

    void Draw(gfx::ICanvas& canvas) const final
    {
        const IStyle& outlineStyle = GetOutlineStyle();
        const IStyle& fillStyle = GetFillStyle();

        if (fillStyle.IsEnabled() && fillStyle.GetColor().has_value())
        {
            canvas.BeginFill(fillStyle.GetColor().value());
        }
        if (outlineStyle.IsEnabled() && outlineStyle.GetColor().has_value())
        {
            canvas.SetLineColor(outlineStyle.GetColor().value());
        }
        else
        {
            canvas.SetLineColor({});
        }

        const auto [left, top, width, height] = GetFrame().value();
        const std::vector<std::pair<double, double>> vertices = {
                {left + width / 2, top},
                {left,             top + height},
                {left + width,     top + height}
        };

        canvas.DrawPolygon(vertices);
        canvas.EndFill();
    }
};