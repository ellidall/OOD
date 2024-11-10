#pragma once

#include <iostream>
#include <cstdint>

namespace graphics_lib
{
    using namespace std;

    class ICanvas
    {
    public:
        virtual void SetColor(uint32_t rgbColor) = 0;
        virtual void MoveTo(int x, int y) = 0;
        virtual void LineTo(int x, int y) = 0;
        virtual ~ICanvas() = default;
    };

    class Canvas : public ICanvas
    {
    public:
        void SetColor(uint32_t rgbColor) override
        {
            cout << "SetColor (" << rgbColor << ")" << endl;
        }

        void MoveTo(int x, int y) override
        {
            cout << "MoveTo (" << x << ", " << y << ")" << endl;
        }

        void LineTo(int x, int y) override
        {
            cout << "LineTo (" << x << ", " << y << ")" << endl;
        }
    };
}