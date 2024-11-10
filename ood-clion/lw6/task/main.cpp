#include <iostream>
#include <string>

#include "graphics_lib.h"
#include "modern_graphics_lib.h"
#include "shape_drawing_lib.h"

#include "ModernGraphicsAdapter.h"

namespace app
{
    void PaintPicture(shape_drawing_lib::CanvasPainter& painter)
    {
        using namespace shape_drawing_lib;

        const Triangle triangle({100, 100}, {200, 200}, {300, 100});
        const Rectangle rectangle({200, 200}, 300, 100);

        painter.Draw(triangle);
        painter.Draw(rectangle);
    }

    void PaintPictureOnCanvas()
    {
        graphics_lib::Canvas simpleCanvas;
        shape_drawing_lib::CanvasPainter painter(simpleCanvas);

        PaintPicture(painter);
    }

    void PaintPictureOnModernGraphicsRenderer()
    {
        modern_graphics_lib::ModernGraphicsRenderer renderer(std::cout);
        app::ModernGraphicsAdapter modernGraphicsAdapter(renderer);
        shape_drawing_lib::CanvasPainter painter(modernGraphicsAdapter);

        renderer.BeginDraw();
        PaintPicture(painter);
        renderer.EndDraw();
    }
}


int main()
{
    app::PaintPictureOnModernGraphicsRenderer();
    std::cout << "-----------------------------" << std::endl;
    app::PaintPictureOnCanvas();
    return EXIT_SUCCESS;
}

// написать пример использования для адаптера класса

// решить проблему того, чтобы не было проблем с вызовом бегин и ендЮ так как теперь наследование теперь приватное