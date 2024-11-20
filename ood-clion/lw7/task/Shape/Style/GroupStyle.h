#pragma once

#include <memory>
#include <vector>

#include "IStyle.h"
#include "IGroupStyle.h"

class GroupStyle : public IGroupStyle
{
public:
    GroupStyle() = default;

    void InsertStyle(IStyle& style, size_t position) override
    {
        m_styles.insert({position, style});
    }

    void RemoveStyleAtIndex(size_t index) override
    {
        auto it = m_styles.find(index);
        if (it != m_styles.end())
        {
            m_styles.erase(it);
        }
    }

    [[nodiscard]] std::optional<bool> IsEnabled() const override
    {
        if (m_styles.empty())
        {
            return std::nullopt;
        }

        std::optional<bool> commonEnabled = std::nullopt;
        for (const auto& pair : m_styles)
        {
            if (commonEnabled == std::nullopt)
            {
                commonEnabled = pair.second.IsEnabled();
            }

            const auto styleEnabled = pair.second.IsEnabled();
            if (commonEnabled != styleEnabled)
            {
                return std::nullopt;
            }
        }
        return commonEnabled;
    }

    void Enable(bool enabled) override
    {
        m_enabled = enabled;
        for (const auto& pair : m_styles)
        {
            pair.second.Enable(enabled);
        }
    }

    [[nodiscard]] std::optional<RGBAColor> GetColor() const override
    {
        if (m_styles.empty())
        {
            return std::nullopt;
        }

        std::optional<RGBAColor> commonColor = std::nullopt;
        for (const auto& pair : m_styles)
        {
            if (commonColor == std::nullopt)
            {
                commonColor = pair.second.GetColor();
            }

            const auto styleColor = pair.second.GetColor();
            if (commonColor != styleColor)
            {
                return std::nullopt;
            }
        }
        return commonColor;
    }

    void SetColor(RGBAColor color) override
    {
        m_color = color;
        for (const auto& pair : m_styles)
        {
            pair.second.SetColor(color);
        }
    }

private:
    std::optional<bool> m_enabled;
    std::optional<RGBAColor> m_color;
    std::map<size_t, IStyle&> m_styles;
};