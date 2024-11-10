#pragma once

#include <optional>
#include <string>
#include <utility>
#include <vector>
#include "../CDocumentItem.h"
#include "AbstractCommand.h"
#include "../Paragraph/CParagraph.h"

class InsertParagraphCommand : public AbstractCommand
{
public:
    InsertParagraphCommand(std::string text, const std::optional<size_t> position, std::vector<CDocumentItem>& items)
            : m_text(std::move(text)), m_position(position), m_items(items)
    {}

    void DoExecute() override
    {
        const auto paragraph = std::make_shared<CParagraph>(m_text);
        const CDocumentItem documentItem(paragraph);

        if (!m_position.has_value())
        {
            m_items.push_back(documentItem);
            return;
        }

        const size_t position = m_position.value();
        if (position > m_items.size()) throw std::invalid_argument("Position out of range");
        m_items.insert(m_items.begin() + static_cast<std::vector<int>::difference_type>(position), documentItem);
    }

    void DoUnexecute() override
    {
        if (m_items.empty()) return;

        if (!m_position.has_value())
        {
            m_items.pop_back();
            return;
        }

        const size_t position = m_position.value();
        if (position < m_items.size())
        {
            m_items.erase(
                    m_items.begin() + static_cast<std::vector<CDocumentItem>::iterator::difference_type>(position));
        }
    }

    void Destroy() override
    {
    }

private:
    std::string m_text;
    std::optional<size_t> m_position;
    std::vector<CDocumentItem>& m_items;
};