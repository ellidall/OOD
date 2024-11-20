#pragma once

#include <cstdint>
#include <limits>
#include <memory>
#include "IStyle.h"

class IStyles
{
public:
    virtual void InsertStyle(IStyle& style, size_t position) = 0;
    virtual void RemoveStyleAtIndex(size_t index) = 0;
    virtual ~IStyles() = default;
};