#pragma once

#include <optional>
#include "IShape.h"

class Shape : public IShape
{
public:
    Shape(const RectD& frame, std::unique_ptr<IStyle> outlineStyle, std::unique_ptr<IStyle> fillStyle)
            : m_outlineStyle(std::move(outlineStyle)), m_fillStyle(std::move(fillStyle))
    {
        m_frame = std::optional<RectD>(frame);
    }

    [[nodiscard]] std::optional<RectD> GetFrame() const override
    {
        return m_frame;
    }

    void SetFrame(const RectD& rect) override
    {
        m_frame = rect;
    }

    [[nodiscard]] IStyle& GetOutlineStyle() override
    {
        return *m_outlineStyle;
    }

    [[nodiscard]] const IStyle& GetOutlineStyle() const override
    {
        return *m_outlineStyle;
    }

    [[nodiscard]] IStyle& GetFillStyle() override
    {
        return *m_fillStyle;
    }

    [[nodiscard]] const IStyle& GetFillStyle() const override
    {
        return *m_fillStyle;
    }

    [[nodiscard]] std::shared_ptr<IGroupShape> GetGroup() override
    {
        return nullptr;
    }

    [[nodiscard]] std::shared_ptr<const IGroupShape> GetGroup() const override
    {
        return nullptr;
    }

private:
    std::optional<RectD> m_frame = std::nullopt;
    std::unique_ptr<IStyle> m_outlineStyle;
    std::unique_ptr<IStyle> m_fillStyle;
};