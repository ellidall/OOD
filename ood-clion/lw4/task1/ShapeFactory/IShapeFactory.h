#pragma once

#include <memory>
#include <string>
#include "Shape/Shape.h"

class IShapeFactory
{
public:
    virtual ~IShapeFactory() = default;
    virtual std::unique_ptr<Shape> CreateShape(const std::string& description) = 0;
};