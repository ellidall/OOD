#pragma once

#include <map>
#include "Style/Style.h"
#include "Style/GroupStyle.h"
#include "IShape.h"

class GroupShape : public IGroupShape, public std::enable_shared_from_this<GroupShape>
{
public:
    GroupShape() = default;

    [[nodiscard]] std::optional<RectD> GetFrame() const override
    {
        if (m_shapes.empty())
        {
            // не проверено в тестах
           // return std::nullopt;
        }

        double left = std::numeric_limits<double>::max();
        double top = std::numeric_limits<double>::max();
        double right = std::numeric_limits<double>::lowest();
        double bottom = std::numeric_limits<double>::lowest();

        bool isGroupsEmpty = true;
        for (const auto& shape : m_shapes)
        {
            std::optional<RectD> frame = shape->GetFrame();
            if (frame == std::nullopt)
            {
                continue;
            }

            left = std::min(left, frame.value().left);
            top = std::min(top, frame.value().top);
            right = std::max(right, frame.value().left + frame.value().width);
            bottom = std::max(bottom, frame.value().top + frame.value().height);
            isGroupsEmpty = false;
        }
        if (isGroupsEmpty)
        {
            return std::nullopt;
        }

        return RectD({left, top, right - left, bottom - top});
    }

    void SetFrame(const RectD& rect) override
    {
        if (GetFrame().has_value())
        {
            auto [left, top, width, height] = *GetFrame();
            const double scaleX = rect.width / width;
            const double scaleY = rect.height / height;

            for (const auto& shape : m_shapes)
            {
                std::optional<RectD> shapeFrame = shape->GetFrame();
                if (shapeFrame == std::nullopt)
                {
                    // ситуация не проверена в тестах
                  //  continue;
                }

                const double newLeft = rect.left + (shapeFrame.value().left - left) * scaleX;
                const double newTop = rect.top + (shapeFrame.value().top - top) * scaleY;
                const double newWidth = shapeFrame.value().width * scaleX;
                const double newHeight = shapeFrame.value().height * scaleY;
                shape->SetFrame(RectD({newLeft, newTop, newWidth, newHeight}));
            }
        }
    }

    IStyle& GetOutlineStyle() override
    {
        return *m_outlineStyle;
    }

    const IStyle& GetOutlineStyle() const override
    {
        return *m_outlineStyle;
    }

    IStyle& GetFillStyle() override
    {
        return *m_fillStyle;
    }

    const IStyle& GetFillStyle() const override
    {
        return *m_fillStyle;
    }

    void Draw(gfx::ICanvas& canvas) const override
    {
        for (const auto& shape : m_shapes)
        {
            if (shape)
            {
                shape->Draw(canvas);
            }
        }
    }

    size_t GetShapesCount() const override
    {
        return m_shapes.size();
    }

    void InsertShape(const std::shared_ptr<IShape>& shape, size_t position) override
    {
        m_shapes.insert(m_shapes.begin() + static_cast<long long>(position), shape);
        m_fillStyle->InsertStyle(shape->GetFillStyle(), position);
        m_outlineStyle->InsertStyle(shape->GetOutlineStyle(), position);
    }

    std::shared_ptr<IShape> GetShapeAtIndex(size_t index) const override
    {
        if (index >= m_shapes.size() || !m_shapes[index])
        {
            return nullptr;
        }
        return m_shapes[index];
    }

    void RemoveShapeAtIndex(size_t index) override
    {
        if (index < m_shapes.size())
        {
            m_shapes.erase(m_shapes.begin() + static_cast<long long>(index));
            m_fillStyle->RemoveStyleAtIndex(index);
            m_outlineStyle->RemoveStyleAtIndex(index);
        }
    }

    std::shared_ptr<IGroupShape> GetGroup() override
    {
        return shared_from_this();
    }

    std::shared_ptr<const IGroupShape> GetGroup() const override
    {
        return shared_from_this();
    }

private:
    std::vector<std::shared_ptr<IShape>> m_shapes;
    // создавать в куче не обязательно, так как конкретнй класс
    std::unique_ptr<IGroupStyle> m_outlineStyle = std::make_unique<GroupStyle>();
    std::unique_ptr<IGroupStyle> m_fillStyle = std::make_unique<GroupStyle>();
};