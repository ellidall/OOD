#pragma once

#include "IStyle.h"
#include "IStyles.h"

class IGroupStyle : public IStyle, public IStyles
{
public:
    virtual ~IGroupStyle() = default;
};