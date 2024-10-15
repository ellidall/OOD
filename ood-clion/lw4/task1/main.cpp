#include <iostream>
#include "ShapeFactory/ShapeFactory.h"
#include "Designer/Designer.h"
#include "Painter/Painter.h"
#include "Client.h"
#include "Canvas/PNGCanvas/PNGCanvas.h"

constexpr int CANVAS_WIDTH = 800;
constexpr int CANVAS_HEIGHT = 500;

int main()
{
    try
    {
        PNGCanvas canvas(CANVAS_WIDTH, CANVAS_HEIGHT);
        ShapeFactory shapeFactory;
        Designer designer(shapeFactory);
        Painter painter;
        Client client(designer);
        client.HandleCommand(std::cin, canvas, painter);
        canvas.SaveToFile("../../output.png");
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }


    return EXIT_SUCCESS;
}
