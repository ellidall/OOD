#pragma once

#include <iosfwd>
#include <string>
#include <sstream>
#include <cstdint>
#include <vector>
#include <fstream>
#include <iomanip>
#include "Geom.h"
#include "Tile.h"
#include "CoW.h"

class Image
{
public:
    /**
     * Конструирует изображение заданного размера. Если размеры не являются положительными,
     * выбрасывает исключение std::out_of_range.
     */
    explicit Image(Size size, uint32_t color = 0xFFFFFF) : m_size(size)
    {
        if (size.width <= 0 || size.height <= 0)
        {
            throw std::out_of_range("Image size must be positive");
        }

        int tileRows = (size.height + Tile::SIZE - 1) / Tile::SIZE;
        int tileCols = (size.width + Tile::SIZE - 1) / Tile::SIZE;

        m_tiles.resize(tileRows);
        for (auto& row : m_tiles)
        {
            // снаружи сделать создание обёртки и тайла
            row.resize(tileCols, CoW<Tile>(Tile(color)));
        }
    }

    // Возвращает размер изображения в пикселях.
    [[nodiscard]] Size GetSize() const noexcept
    {
        return m_size;
    }

    /**
     * Возвращает «цвет» пикселя в указанных координатах.
     */
    [[nodiscard]] uint32_t GetPixel(Point p) const noexcept
    {
        if (p.x < 0 || p.x >= m_size.width || p.y < 0 || p.y >= m_size.height)
        {
            return 0xFFFFFF;
        }

        int tileX = p.x / Tile::SIZE;
        int tileY = p.y / Tile::SIZE;
        int pixelX = p.x % Tile::SIZE;
        int pixelY = p.y % Tile::SIZE;

        return m_tiles[tileY][tileX]->GetPixel({pixelX, pixelY});
    }

    /**
     * Задаёт «цвет» пикселя в указанных координатах. Если координаты выходят за пределы изображения
     * действие игнорируется.
     */
    void SetPixel(Point p, uint32_t color)
    {
        if (p.x < 0 || p.x >= m_size.width || p.y < 0 || p.y >= m_size.height)
        {
            return;
        }

        int tileX = p.x / Tile::SIZE;
        int tileY = p.y / Tile::SIZE;
        int pixelX = p.x % Tile::SIZE;
        int pixelY = p.y % Tile::SIZE;

        // Используем метод Write для изменения тайла
        m_tiles[tileY][tileX].Write([&](Tile& tile) {
            tile.SetPixel({pixelX, pixelY}, color);
        });
    }

private:
    Size m_size;
    std::vector<std::vector<CoW<Tile>>> m_tiles;
};


namespace HandleImage
{
    /**
     * Выводит в поток out изображение в виде символов.
     */
    static void Print(const Image& img, std::ostream& out)
    {
        const auto size = img.GetSize();
        for (int y = 0; y < size.height; ++y)
        {
            for (int x = 0; x < size.width; ++x)
            {
                uint32_t color = img.GetPixel({x, y});

                uint8_t r = (color >> 16) & 0xFF;
                uint8_t g = (color >> 8) & 0xFF;
                uint8_t b = color & 0xFF;

                out << std::setw(3) << std::setfill('0') << static_cast<int>(r) << " "
                    << std::setw(3) << std::setfill('0') << static_cast<int>(g) << " "
                    << std::setw(3) << std::setfill('0') << static_cast<int>(b) << " ";
            }
            out << std::endl;
        }
    }

    static void SaveImageToPPM(const Image& image, const std::string& filename)
    {
        std::ofstream file(filename);
        if (!file.is_open())
        {
            throw std::runtime_error("Could not open the file for writing");
        }

        file << "P3\n";
        file << image.GetSize().width << " " << image.GetSize().height << "\n";
        file << "255\n";

        for (int y = 0; y < image.GetSize().height; ++y)
        {
            for (int x = 0; x < image.GetSize().width; ++x)
            {
                uint32_t color = image.GetPixel({x, y});

                uint8_t r = (color >> 16) & 0xFF;
                uint8_t g = (color >> 8) & 0xFF;
                uint8_t b = color & 0xFF;

                file << static_cast<int>(r) << " "
                     << static_cast<int>(g) << " "
                     << static_cast<int>(b) << " ";
            }
            file << std::endl;
        }

        file.close();
    }

    /**
     * Загружает изображение из pixels. Линии изображения разделяются символами \n.
     * Размеры картинки определяются по количеству переводов строки и самой длинной линии.
     */
    static Image LoadImage(const std::string& pixels)
    {
        std::istringstream s(pixels);
        Size size;
        std::string line;
        while (std::getline(s, line))
        {
            size.width = std::max(size.width, static_cast<int>(line.length()));
            ++size.height;
        }

        Image img(size);

        s = std::istringstream(pixels);
        for (int y = 0; y < size.height; ++y)
        {
            if (!std::getline(s, line))
                break;

            int x = 0;
            for (char ch : line)
            {
                img.SetPixel({x++, y}, ch);
            }
        }

        return img;
    }
}

