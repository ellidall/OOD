#pragma once

#include "graphics_lib.h"
#include "modern_graphics_lib.h"

namespace app
{
    class ModernGraphicsClassAdapter : public graphics_lib::ICanvas, public modern_graphics_lib::ModernGraphicsRenderer
    {
    public:
        explicit ModernGraphicsClassAdapter(std::ostream& strm)
                : ModernGraphicsRenderer(strm),
                  m_start(0, 0),
                  m_color(0, 0, 0, 0)
        {}

        void SetColor(uint32_t rgbColor) override
        {
            float a = ((rgbColor >> 24) & 0xFF) / 255.0f;
            float r = ((rgbColor >> 16) & 0xFF) / 255.0f;
            float g = ((rgbColor >> 8) & 0xFF) / 255.0f;
            float b = (rgbColor & 0xFF) / 255.0f;

            m_color = {r, g, b, a};
        }

        void MoveTo(int x, int y) override
        {
            m_start = {x, y};
        }

        void LineTo(int x, int y) override
        {
            modern_graphics_lib::Point end(x, y);
            DrawLine(m_start, end, m_color);
            m_start = end;
        }

    private:
        modern_graphics_lib::RGBAColor m_color;
        modern_graphics_lib::Point m_start;
    };
}