////#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "stb_image_write.h"
////#endif // STB_IMAGE_WRITE_IMPLEMENTATION
////#ifndef STB_TRUETYPE_IMPLEMENTATION
//#define STB_TRUETYPE_IMPLEMENTATION
//#include "stb_truetype.h"
////#endif // STB_TRUETYPE_IMPLEMENTATION

#pragma once

#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <vector>
#include <cstdint>
#include "../ICanvas.h"

#ifndef PNG_CANVAS_H
#define PNG_CANVAS_H

namespace gfx
{
    struct Color
    {
        uint8_t r, g, b, a;
    };

    Color StringToColor(uint32_t color);

    class PNGCanvas : public ICanvas
    {
    public:
        PNGCanvas(int w, int h)
                : m_width(w),
                  m_height(h),
                  m_currentLineColor({255, 255, 255, 255}),
                  m_currentFillColor({255, 255, 255, 255})
        {
            pixels.resize(m_width * m_height * 4, 255);
        }

        void SetLineColor(uint32_t color) override
        {
            m_currentLineColor = StringToColor(color);
        }

        void BeginFill(uint32_t color) override
        {
            m_currentFillColor = StringToColor(color);
        }

        void EndFill() override
        {
            m_currentFillColor = {255, 255, 255, 255};
        }

        void DrawPolygon(const std::vector<std::pair<double, double>>& vertices) override
        {
            if (vertices.size() < 3)
            {
                return;
            }

            FillPolygon(vertices);

            for (size_t i = 0; i < vertices.size(); ++i)
            {
                size_t nextIndex = (i + 1) % vertices.size();
                DrawLine(vertices[i].first, vertices[i].second, vertices[nextIndex].first, vertices[nextIndex].second);
            }
        }

        void DrawLine(double fromX, double fromY, double toX, double toY)
        {
            int ix1 = static_cast<int>(std::round(fromX));
            int iy1 = static_cast<int>(std::round(fromY));
            int ix2 = static_cast<int>(std::round(toX));
            int iy2 = static_cast<int>(std::round(toY));

            int dx = std::abs(ix2 - ix1), dy = std::abs(iy2 - iy1);
            int sx = (ix1 < ix2) ? 1 : -1;
            int sy = (iy1 < iy2) ? 1 : -1;
            int err = dx - dy;

            while (true)
            {
                PutPixel(ix1, iy1, m_currentLineColor);
                if (ix1 == ix2 && iy1 == iy2) break;
                int e2 = 2 * err;
                if (e2 > -dy)
                {
                    err -= dy;
                    ix1 += sx;
                }
                if (e2 < dx)
                {
                    err += dx;
                    iy1 += sy;
                }
            }
        }

        void DrawEllipse(double cx, double cy, double rx, double ry)
        {
            int segments = 100;
            double angleStep = 2 * M_PI / segments;

            std::vector<std::pair<double, double>> vertices;
            for (int i = 0; i <= segments; ++i)
            {
                double angle = i * angleStep;
                double newX = cx + rx * cos(angle);
                double newY = cy + ry * sin(angle);
                vertices.emplace_back(newX, newY);
            }

            FillPolygon(vertices);

            for (size_t i = 0; i < vertices.size() - 1; ++i)
            {
                DrawLine(vertices[i].first, vertices[i].second, vertices[i + 1].first, vertices[i + 1].second);
            }
        }

        void SaveToFile(const std::string& filename);

    private:
        int m_width, m_height;
        Color m_currentLineColor{};
        Color m_currentFillColor{};
        std::vector<uint8_t> pixels;

        void PutPixel(int x, int y, Color color)
        {
            if (x >= 0 && x < m_width && y >= 0 && y < m_height)
            {
                int index = 4 * (y * m_width + x);
                pixels[index] = color.r;
                pixels[index + 1] = color.g;
                pixels[index + 2] = color.b;
                pixels[index + 3] = color.a;
            }
        }

        void FillPolygon(const std::vector<std::pair<double, double>>& vertices)
        {
            // Определяем границы многоугольника
            double minX = vertices[0].first;
            double maxX = vertices[0].first;
            double minY = vertices[0].second;
            double maxY = vertices[0].second;

            for (const auto& vertex : vertices)
            {
                if (vertex.first < minX) minX = vertex.first;
                if (vertex.first > maxX) maxX = vertex.first;
                if (vertex.second < minY) minY = vertex.second;
                if (vertex.second > maxY) maxY = vertex.second;
            }

            // Обход всех точек в границах многоугольника
            for (int y = static_cast<int>(minY); y <= static_cast<int>(maxY); ++y)
            {
                for (int x = static_cast<int>(minX); x <= static_cast<int>(maxX); ++x)
                {
                    // Проверяем, находится ли точка внутри многоугольника
                    bool inside = false;
                    for (size_t i = 0, j = vertices.size() - 1; i < vertices.size(); j = i++)
                    {
                        const auto& v1 = vertices[i];
                        const auto& v2 = vertices[j];

                        if (((v1.second > y) != (v2.second > y)) &&
                            (x < (v2.first - v1.first) * (y - v1.second) / (v2.second - v1.second) + v1.first))
                        {
                            inside = !inside;
                        }
                    }

                    if (inside)
                    {
                        PutPixel(x, y, m_currentFillColor);
                    }
                }
            }
        }

    };
}

#endif // PNG_CANVAS_H
