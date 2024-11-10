#pragma once

#include <format>
#include "Document/IDocument.h"
#include "Menu/CMenu.h"
#include "Document/Command/AbstractCommand.h"
#include "Document/Paragraph/CParagraph.h"
#include "Document/History/History.h"

class CommandHandler
{
public:
    CommandHandler(CMenu& menu, IDocument& document) : m_menu(menu), m_document(document)
    {
        AddMenuItem(
                "InsertParagraph",
                "Usage: InsertParagraph <position>|end <text>. Inserts a paragraph into the specified position.",
                std::bind(&CommandHandler::InsertParagraph, this, std::placeholders::_1)
        );
        AddMenuItem(
                "InsertImage",
                "Usage: InsertImage <position>|end <width> <height> <image-path>. Inserts an image with the specified width and height.",
                std::bind(&CommandHandler::InsertImage, this, std::placeholders::_1)
        );
        AddMenuItem(
                "SetTitle",
                "Usage: SetTitle <title>. Sets the document title.",
                std::bind(&CommandHandler::SetTitle, this, std::placeholders::_1)
        );
        AddMenuItem(
                "List",
                "Usage: List. Displays the title and list of document elements.",
                std::bind(&CommandHandler::List, this, std::placeholders::_1)
        );
        AddMenuItem(
                "ReplaceText",
                "Usage: ReplaceText <position> <text>. Replaces the text in the paragraph by the specified position.",
                std::bind(&CommandHandler::ReplaceText, this, std::placeholders::_1)
        );
        AddMenuItem(
                "ResizeImage",
                "Usage: ResizeImage <position> <width> <height>. Resizes the image at the specified position.",
                std::bind(&CommandHandler::ResizeImage, this, std::placeholders::_1)
        );
        AddMenuItem(
                "DeleteItem",
                "Usage: DeleteItem <position>. Deletes an item at the specified position.",
                std::bind(&CommandHandler::DeleteItem, this, std::placeholders::_1)
        );
        AddMenuItem(
                "Help",
                "Usage: Help. Shows the available commands.",
                std::bind(&CommandHandler::Help, this, std::placeholders::_1)
        );
        AddMenuItem(
                "Undo",
                "Usage: Undo. Cancels the last action.",
                std::bind(&CommandHandler::Undo, this, std::placeholders::_1)
        );
        AddMenuItem(
                "Redo",
                "Usage: Redo. Repeats the last canceled action.",
                std::bind(&CommandHandler::Redo, this, std::placeholders::_1)
        );
        AddMenuItem(
                "Save",
                "Usage: Save <path>. Saves the document to a file.",
                std::bind(&CommandHandler::Save, this, std::placeholders::_1)
        );
        AddMenuItem(
                "Exit",
                "Usage: Exit. Exits the program.",
                std::bind(&CommandHandler::Exit, this, std::placeholders::_1)
        );
    }
private:
    CMenu& m_menu;
    IDocument& m_document;

    void AddMenuItem(const std::string& shortcut, const std::string& description, const Command& command)
    {
        m_menu.AddItem(shortcut, description, command);
    }

    void InsertParagraph(std::istringstream& params)
    {
        std::string positionInput;
        std::string text;

        if (!(params >> positionInput >> text))
        {
            std::cerr << "Invalid arguments." << std::endl;
            return;
        }

        std::optional<size_t> position = std::nullopt;
        if (positionInput != "end")
        {
            try
            {
                position = std::stoi(positionInput);
            }
            catch (std::invalid_argument&)
            {
                std::cerr << "Error: The position must be an uint or 'end'." << std::endl;
                return;
            }
        }

        m_document.InsertParagraph(text, position);
    }

    void InsertImage(std::istringstream& params)
    {
        std::string positionInput;
        unsigned width;
        unsigned height;
        std::string imagePath;

        if (!(params >> positionInput >> width >> height >> imagePath))
        {
            std::cerr << "Invalid arguments." << std::endl;
            return;
        }

        std::optional<size_t> position = std::nullopt;
        if (positionInput != "end")
        {
            try
            {
                position = std::stoi(positionInput);
            }
            catch (std::invalid_argument&)
            {
                std::cerr << "Error: The position must be an integer or 'end'." << std::endl;
                return;
            }
        }

        m_document.InsertImage(imagePath, width, height, position);
    }

    void SetTitle(std::istringstream& params)
    {
        std::string newTitle;
        params >> newTitle;
        m_document.SetTitle(newTitle);
    }

    void List(std::istringstream&)
    {
        const auto title = m_document.GetTitle();
        const auto itemCount = m_document.GetItemsCount();

        std::cout << "Title: " << title << std::endl;
        for (int i = 0; i < itemCount; ++i)
        {
            auto item = m_document.GetItem(i);
            auto image = item.GetImage();
            auto paragraph = item.GetParagraph();
            std::string description{};

            if (image != nullptr)
            {
                description = std::format("Image: {} {} {}", image->GetWidth(), image->GetHeight(),
                        image->GetPath());
            }

            if (paragraph != nullptr)
            {
                description = std::format("Paragraph: {}", paragraph->GetText());
            }

            std::cout << i + 1 << ". " << description << std::endl;
        }
    }

    void ReplaceText(std::istringstream& params)
    {
        size_t position;
        std::string newText;

        if (!(params >> position >> newText))
        {
            std::cerr << "Invalid arguments." << std::endl;
            return;
        }

        if (newText.empty())
        {
            std::cerr << "Error: text cannot be empty." << std::endl;
            return;
        }

        m_document.ReplaceText(newText, position);
    }

    void ResizeImage(std::istringstream& params)
    {
        size_t position;
        unsigned newWidth;
        unsigned newHeight;

        if (!(params >> position >> newWidth >> newHeight))
        {
            std::cerr << "Invalid arguments." << std::endl;
            return;
        }

        m_document.ResizeImage(position, newWidth, newHeight);
    }

    void DeleteItem(std::istringstream& params)
    {
        size_t position;
        if (!(params >> position))
        {
            std::cerr << "Invalid arguments." << std::endl;
            return;
        }
        m_document.DeleteItem(position);
    }

    void Help(std::istringstream&)
    {
        m_menu.ShowInstructions();
    }

    void Undo(std::istringstream&)
    {
        if (!m_document.CanUndo())
        {
            std::cout << "Cancellation is not possible!" << std::endl;
            return;
        }

        m_document.Undo();
    }

    void Redo(std::istringstream&)
    {
        if (!m_document.CanRedo())
        {
            std::cout << "Repeat is not possible!" << std::endl;
            return;
        }

        m_document.Redo();
    }

    void Save(std::istringstream& params)
    {
        std::string filePath;
        if (!(params >> filePath))
        {
            std::cerr << "Invalid arguments." << std::endl;
            return;
        }
        m_document.Save(filePath);
    }

    void Exit(std::istringstream&)
    {
        m_menu.Exit();
    }
};