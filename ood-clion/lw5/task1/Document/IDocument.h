#pragma once

#include <optional>
#include "CConstDocumentItem.h"
#include "CDocumentItem.h"

class IDocument
{
public:
    virtual void InsertParagraph(const std::string& text, std::optional<size_t> position) = 0;
    virtual void ReplaceText(const std::string& text, size_t position) = 0;
    virtual void InsertImage(const Path& path, unsigned width, unsigned height, std::optional<size_t> position) = 0;
    virtual void ResizeImage(size_t position, unsigned width, unsigned height) = 0;
    [[nodiscard]] virtual size_t GetItemsCount() const = 0;
    [[nodiscard]] virtual CConstDocumentItem GetItem(size_t index) const = 0;
    virtual CDocumentItem GetItem(size_t index) = 0;
    virtual void DeleteItem(size_t index) = 0;
    [[nodiscard]] virtual std::string GetTitle() const = 0;
    virtual void SetTitle(const std::string& title) = 0;
    [[nodiscard]] virtual bool CanUndo() const = 0;
    virtual void Undo() = 0;
    [[nodiscard]] virtual bool CanRedo() const = 0;
    virtual void Redo() = 0;
    virtual void Save(const Path& path) const = 0;
    virtual ~IDocument() = default;
};