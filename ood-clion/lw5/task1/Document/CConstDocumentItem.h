#pragma once

#include <memory>
#include "Image/IImage.h"
#include "Paragraph/IParagraph.h"

class CConstDocumentItem
{
public:
    explicit CConstDocumentItem(std::shared_ptr<const IImage> image) : m_image(std::move(image))
    {}

    explicit CConstDocumentItem(std::shared_ptr<const IParagraph> paragraph) : m_paragraph(std::move(paragraph))
    {}

    virtual ~CConstDocumentItem() = default;

    [[nodiscard]] std::shared_ptr<const IImage> GetImage() const
    {
        return m_image;
    }

    [[nodiscard]] std::shared_ptr<const IParagraph> GetParagraph() const
    {
        return m_paragraph;
    }

private:
    std::shared_ptr<const IImage> m_image = nullptr;
    std::shared_ptr<const IParagraph> m_paragraph = nullptr;
};