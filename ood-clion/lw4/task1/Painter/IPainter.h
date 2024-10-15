#pragma once

#include "../Designer/PictureDraft.h"
#include "../Canvas/ICanvas.h"

class IPainter
{
public:
    virtual ~IPainter() = default;
    virtual void DrawPicture(const PictureDraft& draft, ICanvas& canvas) = 0;
};