#pragma once

#include "IStyle.h"

class Style : public IStyle
{
public:
    explicit Style(std::optional<RGBAColor> color) : m_color(color)
    {}

    [[nodiscard]] std::optional<bool> IsEnabled() const override
    {
        return m_enabled;
    }

    void Enable(bool enable) override
    {
        m_enabled = enable;
    }

    [[nodiscard]] std::optional<RGBAColor> GetColor() const override
    {
        return m_color;
    }

    void SetColor(RGBAColor color) override
    {
        m_color = color;
    }

private:
    std::optional<bool> m_enabled = std::nullopt;
    std::optional<RGBAColor> m_color = std::nullopt;
};
