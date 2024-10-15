#pragma once

#include <istream>
#include "PictureDraft.h"

class IDesigner
{
public:
    virtual ~IDesigner() = default;
    virtual PictureDraft CreateDraft(std::istream& inputData) = 0;
};
