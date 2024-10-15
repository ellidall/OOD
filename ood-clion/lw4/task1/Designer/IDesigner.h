#pragma once

#include <istream>
#include "PictureDraft.h"

class IDesigner
{
public:
    // TODO зачем тут виртуальный деструктор и какие альтернативы
    virtual ~IDesigner() = default;
    virtual PictureDraft CreateDraft(std::istream& inputData) = 0;
};
