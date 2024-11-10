#pragma once

#include "CConstDocumentItem.h"
#include "Image/IImage.h"
#include "Paragraph/IParagraph.h"

class CDocumentItem : public CConstDocumentItem
{
public:
    explicit CDocumentItem(std::shared_ptr<IImage> image) : CConstDocumentItem(image), m_image(std::move(image))
    {}

    explicit CDocumentItem(std::shared_ptr<IParagraph> paragraph) : CConstDocumentItem(paragraph),
                                                                    m_paragraph(std::move(paragraph))
    {}

    std::shared_ptr<IImage> GetImage()
    {
        return m_image;
    }

    std::shared_ptr<IParagraph> GetParagraph()
    {
        return m_paragraph;
    }

private:
    std::shared_ptr<IImage> m_image = nullptr;
    std::shared_ptr<IParagraph> m_paragraph = nullptr;
};