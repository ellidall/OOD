#pragma once

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "../ICanvas.h"
#include <memory>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>

class PNGCanvas : public ICanvas
{
public:
	using Color = uint32_t;

	struct ColorStruct
	{
		uint8_t r, g, b, a;
	};

	PNGCanvas(const unsigned width, const unsigned height)
		: m_width(width), m_height(height)
	{
		m_pixels.resize(width * height * 4, 255);
	}

	void SetColor(const Color color) override
	{
		ColorStruct result{};

		result.r = static_cast<uint8_t>((color >> 24) & 0xFF);
		result.g = static_cast<uint8_t>((color >> 16) & 0xFF);
		result.b = static_cast<uint8_t>((color >> 8) & 0xFF);
		result.a = static_cast<uint8_t>(color & 0xFF);

		m_color = result;
	}

	void MoveTo(const double x, const double y) override
	{
		m_currentPosition = {x, y};
	}

	void LineTo(const double x, const double y) override
	{
		DrawLine(m_currentPosition.x, m_currentPosition.y, x, y);
		m_currentPosition = {x, y};
	}

	void DrawEllipse(const double cx, const double cy, const double rx, const double ry) override
	{
		constexpr int segments = 100;
		constexpr double angleStep = 2 * M_PI / segments;

		double prevX = cx + rx;
		double prevY = cy;

		for (int i = 1; i <= segments; ++i)
		{
			const double angle = i * angleStep;
			const double newX = cx + rx * cos(angle);
			const double newY = cy + ry * sin(angle);
			DrawLine(prevX, prevY, newX, newY);
			prevX = newX;
			prevY = newY;
		}
	}

	void SaveToFile(const std::string &filename) const
	{
		stbi_write_png(
			filename.c_str(),
			static_cast<int>(m_width),
			static_cast<int>(m_height),
			4, m_pixels.data(),
			static_cast<int>(m_width) * 4
		);
	};

private:
	unsigned m_width;
	unsigned m_height;
	ColorStruct m_color{};
	Point m_currentPosition = {0, 0};
	std::vector<uint8_t> m_pixels;

	void PutPixel(const int x, const int y)
	{
		if (x >= 0 && x < m_width && y >= 0 && y < m_height)
		{
			const auto index = 4 * (y * m_width + x);
			m_pixels[index] = m_color.r;
			m_pixels[index + 1] = m_color.g;
			m_pixels[index + 2] = m_color.b;
			m_pixels[index + 3] = m_color.a;
		}
	}

	void DrawLine(const double x1, const double y1, const double x2, const double y2)
	{
		int ix1 = static_cast<int>(std::round(x1));
		int iy1 = static_cast<int>(std::round(y1));
		const int ix2 = static_cast<int>(std::round(x2));
		const int iy2 = static_cast<int>(std::round(y2));

		int dx = std::abs(ix2 - ix1), dy = std::abs(iy2 - iy1);
		const int sx = (ix1 < ix2) ? 1 : -1;
		const int sy = (iy1 < iy2) ? 1 : -1;
		int err = dx - dy;

		while (true)
		{
			PutPixel(ix1, iy1);
			if (ix1 == ix2 && iy1 == iy2)
				break;
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
};