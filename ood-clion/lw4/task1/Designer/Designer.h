#pragma once

#include "IDesigner.h"
#include "../ShapeFactory/IShapeFactory.h"
#include "PictureDraft.h"

class Designer : public IDesigner
{
public:
    explicit Designer(IShapeFactory& factory) : m_factory(factory)
    {}

    PictureDraft CreateDraft(std::istream& inputData) override
    {
        PictureDraft draft;
        std::string line;
        while (getline(inputData, line))
        {
            if (line == "exit") break;
            draft.AddShape(std::move(m_factory.CreateShape(line)));
        }
        return draft;
    }

private:
    IShapeFactory& m_factory;
};