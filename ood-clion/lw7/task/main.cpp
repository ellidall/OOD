#include <iostream>
#include <fstream>
#include <cassert>
#include "Canvas/PNGCanvas/PNGCanvas.h"
#include "ShapeFactory/ShapeFactory.h"
#include "Slide/SlideService.h"

const std::string STANDARD_INPUT_STREAM = "cin";
const std::string PICTURE_OUTPUT_FILE_PATH = "../../output.png";

const int CANVAS_WIDTH = 800;
const int CANVAS_HEIGHT = 800;

void CheckArgs(int argc)
{
    if (argc != 2)
    {
        throw std::invalid_argument("Error: usage <programName> <inputName>");
    }
}

void CheckFileOpen(std::ifstream& inputFile)
{
    if (!inputFile.is_open())
    {
        throw std::runtime_error("Failed to open file");
    }
}

void CheckFileValid(std::ifstream& inputFile)
{
    if (inputFile.peek() == std::ifstream::traits_type::eof())
    {
        throw std::invalid_argument("Error: input file is empty");
    }
}

void HandleCommand(SlideService& slideService, std::istream& inputData, gfx::ICanvas& canvas)
{
    slideService.CreateSlide(inputData, CANVAS_WIDTH, CANVAS_HEIGHT);
    slideService.DrawSlide(canvas);
}

int main(int argc, char* argv[])
{
//    try
//    {
//        CheckArgs(argc);
//        gfx::PNGCanvas canvas(CANVAS_WIDTH, CANVAS_HEIGHT);
//        ShapeFactory shapeFactory;
//        SlideService slideService(shapeFactory);
//
//        if (argv[1] == STANDARD_INPUT_STREAM)
//        {
//            HandleCommand(slideService, std::cin, canvas);
//        }
//        else
//        {
//            std::ifstream input(argv[1]);
//            CheckFileOpen(input);
//            CheckFileValid(input);
//            HandleCommand(slideService, input, canvas);
//        }
//        canvas.SaveToFile(PICTURE_OUTPUT_FILE_PATH);
//    }
//    catch (const std::exception& e)
//    {
//        std::cerr << e.what() << std::endl;
//        return EXIT_FAILURE;
//    }

    auto group = std::make_shared<GroupShape>();

    ShapeFactory shapeFactory;
    std::string desc1 = "rectangle #ADD8E6 #0000FF 100 100 100 100";
    std::string desc2 = "rectangle #ADD8E6 #0000FF 100 200 50 50";
    std::string desc3 = "rectangle #ADD8E6 #FF00FF 100 250 100 100";
    auto rect1 = shapeFactory.CreateShape(desc1);
    auto rect2 = shapeFactory.CreateShape(desc2);
    auto rect3 = shapeFactory.CreateShape(desc3);

    group->InsertShape(rect1, 0);
    group->InsertShape(rect2, 1);

    Slide slide(800, 800, group);

    IStyle& style = group->GetFillStyle();
    auto* groupStyle = dynamic_cast<GroupStyle*>(&style);
    group->InsertShape(rect3, 2);
    groupStyle->SetColor(0xFF0000FF);

    gfx::PNGCanvas canvas(CANVAS_WIDTH, CANVAS_HEIGHT);
    slide.Draw(canvas);
    canvas.SaveToFile("../../out.png");

    return EXIT_SUCCESS;
}
