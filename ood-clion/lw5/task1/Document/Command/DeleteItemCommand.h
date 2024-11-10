#pragma once

#include <vector>
#include "../CDocumentItem.h"
#include "AbstractCommand.h"

class DeleteItemCommand final : public AbstractCommand
{
public:
    DeleteItemCommand(const size_t index, std::vector<CDocumentItem>& items) : m_index(index), m_items(items)
    {}

    void DoExecute() override
    {
        if (m_index >= m_items.size()) throw std::invalid_argument("Index out of range");

        m_currentItem = std::make_unique<CDocumentItem>(m_items.at(m_index));
        m_items.erase(m_items.begin() + static_cast<std::vector<CDocumentItem>::iterator::difference_type>(m_index));
    }

    void DoUnexecute() override
    {
        if (m_currentItem == nullptr) return;

        m_items.insert(
                m_items.begin() + static_cast<std::vector<CDocumentItem>::iterator::difference_type>(m_index),
                *m_currentItem);

        m_currentItem = nullptr;
    }

    void Destroy() override
    {}

private:
    size_t m_index;
    std::unique_ptr<CDocumentItem> m_currentItem = nullptr;
    std::vector<CDocumentItem>& m_items;
};