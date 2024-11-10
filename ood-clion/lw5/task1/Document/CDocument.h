#pragma once

#include <vector>
#include "History/History.h"
#include "IDocument.h"
#include "Command/DeleteItemCommand.h"
#include "Command/InsertImageCommand.h"
#include "Command/InsertParagraphCommand.h"
#include "Command/ReplaceTextCommand.h"
#include "Command/ResizeImageCommand.h"
#include "Command/SetTitleCommand.h"
#include "Utils/HtmlUtils.h"

class CDocument : public IDocument
{
public:
    void InsertParagraph(const std::string& text, std::optional<size_t> position) override
    {
        m_history.AddAndExecuteCommand(std::make_unique<InsertParagraphCommand>(text, position, m_items));
    }

    void ReplaceText(const std::string& text, size_t position) override
    {
        m_history.AddAndExecuteCommand(std::make_unique<ReplaceTextCommand>(text, position, m_items));
    }

    void InsertImage(const Path& path, unsigned width, unsigned height, std::optional<size_t> position) override
    {
        m_history.AddAndExecuteCommand(std::make_unique<InsertImageCommand>(path, width, height, position, m_items));
    }

    void ResizeImage(size_t position, unsigned width, unsigned height) override
    {
        m_history.AddAndExecuteCommand(std::make_unique<ResizeImageCommand>(position, width, height, m_items));
    }

    [[nodiscard]] size_t GetItemsCount() const override
    {
        return m_items.size();
    }

    [[nodiscard]] CConstDocumentItem GetItem(const size_t index) const override
    {
        if (index >= m_items.size()) throw std::invalid_argument("Index out of range");
        return static_cast<CConstDocumentItem>(m_items[index]);
    }

    CDocumentItem GetItem(const size_t index) override
    {
        if (index >= m_items.size()) throw std::invalid_argument("Index out of range");
        return m_items[index];
    }

    void DeleteItem(const size_t index) override
    {
        m_history.AddAndExecuteCommand(std::make_unique<DeleteItemCommand>(index, m_items));
    }

    [[nodiscard]] std::string GetTitle() const override
    {
        return m_title;
    }

    void SetTitle(const std::string& title) override
    {
        m_history.AddAndExecuteCommand(std::make_unique<SetTitleCommand>(m_title, title));
    }

    [[nodiscard]] bool CanUndo() const override
    {
        return m_history.CanUndo();
    }

    void Undo() override
    {
        m_history.Undo();
    }

    [[nodiscard]] bool CanRedo() const override
    {
        return m_history.CanRedo();
    }

    void Redo() override
    {
        m_history.Redo();
    }

    void Save(const Path& path) const override
    {
        std::vector<CConstDocumentItem> constItems{};

        for (const auto& item : m_items)
        {
            constItems.emplace_back(static_cast<CConstDocumentItem>(item));
        }

        HtmlUtils::CreateHtmlFile(m_title, constItems, path);
    }

private:
    std::string m_title;
    std::vector<CDocumentItem> m_items;
    History m_history;
};