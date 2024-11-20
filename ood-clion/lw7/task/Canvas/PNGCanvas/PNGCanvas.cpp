#include "PNGCanvas.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

namespace gfx
{
    gfx::Color StringToColor(uint32_t color) {
        gfx::Color result{};

        result.r = static_cast<uint8_t>((color >> 24) & 0xFF);
        result.g = static_cast<uint8_t>((color >> 16) & 0xFF);
        result.b = static_cast<uint8_t>((color >> 8) & 0xFF);
        result.a = static_cast<uint8_t>(color & 0xFF);

        return result;
    }

    void gfx::PNGCanvas::SaveToFile(const std::string& filename)
    {
        stbi_write_png(filename.c_str(), m_width, m_height, 4, pixels.data(), m_width * 4);
    }
}