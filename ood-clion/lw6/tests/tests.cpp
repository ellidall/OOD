#include <gtest/gtest.h>
#include <sstream>
#include <vector>

#include "../task/graphics_lib.h"
#include "../task/modern_graphics_lib.h"
#include "../task/ModernGraphicsAdapter.h"
#include "../task/ModernGraphicsClassAdapter.h"

namespace m = modern_graphics_lib;
namespace g = graphics_lib;

m::RGBAColor ConvertColorHEXToRGBAColor(uint32_t rgbColor)
{
    float a = ((rgbColor >> 24) & 0xFF) / 255.0f;
    float r = ((rgbColor >> 16) & 0xFF) / 255.0f;
    float g = ((rgbColor >> 8) & 0xFF) / 255.0f;
    float b = (rgbColor & 0xFF) / 255.0f;

    m::RGBAColor color = {r, g, b, a};
    return color;
}

std::string DrawWithoutAdapter(const std::vector<m::Point>& points, uint32_t color)
{
    std::stringstream strm;
    m::ModernGraphicsRenderer renderer(strm);
    auto rgbaColor = ConvertColorHEXToRGBAColor(color);

    const auto first = points.begin();
    renderer.BeginDraw();

    for (auto it = first; it != points.end(); ++it)
    {
        if (it + 1 != points.end())
        {
            renderer.DrawLine(*it, *(it + 1), rgbaColor);
        }
        else
        {
            renderer.DrawLine(*it, *first, rgbaColor);
        }
    }

    renderer.EndDraw();

    return strm.str();
}

void DrawWithAdapter(
        m::ModernGraphicsRenderer& renderer,
        g::ICanvas& adapter,
        const std::vector<m::Point>& points,
        uint32_t color
)
{
    adapter.SetColor(color);
    renderer.BeginDraw();

    auto first = points.begin();
    adapter.MoveTo((*first).x, (*first).y);

    for (auto it = first + 1; it != points.end(); ++it)
    {
        adapter.LineTo((*it).x, (*it).y);
    }

    adapter.LineTo((*first).x, (*first).y);
    renderer.EndDraw();
}

std::string DrawWithObjectAdapter(const std::vector<m::Point>& points, uint32_t color)
{
    std::stringstream strm;
    m::ModernGraphicsRenderer renderer(strm);
    app::ModernGraphicsAdapter adapter(renderer);

    DrawWithAdapter(renderer, adapter, points, color);

    return strm.str();
}

std::string DrawShapeWithClassAdapter(const std::vector<m::Point>& points, uint32_t color)
{
    std::stringstream strm;
    app::ModernGraphicsClassAdapter adapter(strm);

    DrawWithAdapter(adapter, adapter, points, color);

    return strm.str();
}

TEST(TestObjectAdapter, DrawWithObjectAdapter)
{
    std::vector<m::Point> vector = {
            m::Point(10, 15),
            m::Point(100, 200),
            m::Point(150, 250),
            m::Point(20, 150),
            m::Point(130, 250),
    };

    uint32_t color = 0xFF5733FF;

    const auto originalShape = DrawWithoutAdapter(vector, color);
    const auto withAdapterShape = DrawWithObjectAdapter(vector, color);

    EXPECT_EQ(originalShape, withAdapterShape);
}

TEST(TestClassAdapter, DrawWithClassAdapter)
{
    std::vector<m::Point> vector = {
            m::Point(10, 15),
            m::Point(130, 250),
    };

    uint32_t color = 0xFF5733FF;

    const auto originalShape = DrawWithoutAdapter(vector, color);
    const auto withAdapterShape = DrawShapeWithClassAdapter(vector, color);

    EXPECT_EQ(originalShape, withAdapterShape);
}