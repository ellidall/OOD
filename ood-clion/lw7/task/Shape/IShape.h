#pragma once

#include <memory>
#include <optional>
#include "../CommonTypes.h"
#include "../IDrawable.h"
#include "Style/IStyle.h"
#include "IShapes.h"

class IGroupShape;

class IShape : public IDrawable
{
public:
    [[nodiscard]] virtual std::optional<RectD> GetFrame() const = 0;
    virtual void SetFrame(const RectD& rect) = 0;

    virtual IStyle& GetOutlineStyle() = 0;
    [[nodiscard]] virtual const IStyle& GetOutlineStyle() const = 0;

    virtual IStyle& GetFillStyle() = 0;
    [[nodiscard]] virtual const IStyle& GetFillStyle() const = 0;

    virtual std::shared_ptr<IGroupShape> GetGroup() = 0;
    [[nodiscard]] virtual std::shared_ptr<const IGroupShape> GetGroup() const = 0;

    virtual ~IShape() = default;
};

class IGroupShape : public IShape, public IShapes
{
public:
    virtual ~IGroupShape() = default;
};