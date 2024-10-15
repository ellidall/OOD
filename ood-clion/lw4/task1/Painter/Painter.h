#pragma  once
#include "IPainter.h"
#include "../Canvas/ICanvas.h"

class Painter : public IPainter
{
public:
    void DrawPicture(const PictureDraft& draft, ICanvas& canvas) override
    {
        for (const auto& shape : draft) {
            shape->Draw(canvas);
        }
    }
};