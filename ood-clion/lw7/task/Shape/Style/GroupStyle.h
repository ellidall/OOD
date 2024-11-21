#pragma once

#include <memory>
#include <vector>

#include "IStyle.h"
#include "IGroupStyle.h"

class GroupStyle : public IGroupStyle
{
public:
    GroupStyle() = default;

    //без интерфейса IGroupStyle
    void InsertStyle(IStyle& style, size_t position) override
    {
        m_styles.insert(m_styles.begin() + static_cast<long long>(position), style);
    }

    // добавить толщину линии
    // избавиться от дублирования
    void RemoveStyleAtIndex(size_t index) override
    {
        if (index < m_styles.size())
        {
            m_styles.erase(m_styles.begin() + static_cast<long long>(index));
        }
    }

    [[nodiscard]] std::optional<bool> IsEnabled() const override
    {
        if (m_styles.empty())
        {
            return std::nullopt;
        }

        std::optional<bool> commonEnabled = std::nullopt;
        for (const auto& style : m_styles)
        {
            if (commonEnabled == std::nullopt)
            {
                commonEnabled = style.get().IsEnabled();
            }

            const auto styleEnabled = style.get().IsEnabled();
            if (commonEnabled != styleEnabled)
            {
                //проверить в тестах
               // return std::nullopt;
            }
        }
        return commonEnabled;
    }

    void Enable(bool enabled) override
    {
        m_enabled = enabled;
        for (const auto& style : m_styles)
        {
            style.get().Enable(enabled);
        }
    }

    [[nodiscard]] std::optional<RGBAColor> GetColor() const override
    {
        if (m_styles.empty())
        {
            return std::nullopt;
        }

        std::optional<RGBAColor> commonColor = std::nullopt;
        for (const auto& style : m_styles)
        {
            if (commonColor == std::nullopt)
            {
                commonColor = style.get().GetColor();
            }

            const auto styleColor = style.get().GetColor();
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
        for (const auto& style : m_styles)
        {
            style.get().SetColor(color);
        }
    }

private:
    std::optional<bool> m_enabled;
    std::optional<RGBAColor> m_color;
    std::vector<std::reference_wrapper<IStyle>> m_styles;
};