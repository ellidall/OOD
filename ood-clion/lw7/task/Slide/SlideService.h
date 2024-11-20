#pragma once

#include <sstream>
#include <stack>
#include "../ShapeFactory/IShapeFactory.h"
#include "../Shape/GroupShape.h"
#include "../Slide/Slide.h"

class SlideService
{
public:
    constexpr static const std::string startGroup = "startGroup";
    constexpr static const std::string endGroup = "endGroup";

    explicit SlideService(IShapeFactory& shapeFactory) : m_shapeFactory(shapeFactory)
    {}

    void CreateSlide(std::istream& inputData, double width, double height)
    {
        std::string line;
        auto firstGroup = std::make_shared<GroupShape>();
        std::stack<std::shared_ptr<GroupShape>> groupStack;
        groupStack.push(firstGroup);

        while (getline(inputData, line))
        {
            if (line == startGroup)
            {
                auto newGroup = std::make_shared<GroupShape>();
                groupStack.top()->InsertShape(newGroup,groupStack.top()->GetShapesCount());
                groupStack.push(newGroup);
                continue;
            }
            if (line == endGroup)
            {
                if (groupStack.size() > 1)
                {
                    if (groupStack.top()->GetShapesCount() == 0)
                    {
                        groupStack.pop();
                        size_t lastEmptyGroupIndex = groupStack.top()->GetShapesCount() - 1;
                        groupStack.top()->RemoveShapeAtIndex(lastEmptyGroupIndex);
                    }
                    groupStack.pop();
                }
                continue;
            }

            auto shape = m_shapeFactory.CreateShape(line);
            if (shape)
            {
                groupStack.top()->InsertShape(shape, groupStack.top()->GetShapesCount());
            }
        }

        m_currentSlide = std::make_unique<Slide>(width, height, firstGroup);
    }

    void DrawSlide(gfx::ICanvas& canvas)
    {
        if (m_currentSlide != nullptr)
        {
            m_currentSlide->Draw(canvas);
        }
    }

private:
    IShapeFactory& m_shapeFactory;
    std::unique_ptr<ISlide> m_currentSlide;
};