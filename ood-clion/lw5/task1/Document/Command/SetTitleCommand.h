#pragma once

#include <string>
#include <utility>
#include <vector>
#include "AbstractCommand.h"

class SetTitleCommand : public AbstractCommand
{
public:
    explicit SetTitleCommand(std::string& title, std::string newTitle)
            : m_currentTitle(title), m_newTitle(std::move(newTitle))
    {}

    void DoExecute() override
    {
        std::swap(m_currentTitle, m_newTitle);
    }

    void DoUnexecute() override
    {
        std::swap(m_newTitle, m_currentTitle);
    }

    void Destroy() override
    {
    }

private:
    std::string& m_currentTitle;
    std::string m_newTitle;
};