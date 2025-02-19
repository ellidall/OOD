#include <cmath>
#include <iostream>
#include "Drawer.h"

int main()
{
    {
        Image img({100, 100}, 0xFFFFFF);

        Drawer::DrawLine(img, {50, 10}, {80, 30}, 0x00FF00);
        Drawer::DrawLine(img, {80, 30}, {20, 30}, 0x00FF00);
        Drawer::DrawLine(img, {20, 30}, {50, 10}, 0x00FF00);

        Drawer::FillCircle(img, {20, 45}, 15, 0xFF0000);
        Drawer::DrawCircle(img, {80, 45}, 15, 0x000000);

//        HandleImage::Print(img, std::cout);
        HandleImage::SaveImageToPPM(img, "../../task/house.ppm");
    }

    return EXIT_SUCCESS;
}
