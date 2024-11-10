#pragma once

#include <memory>
#include <vector>
#include "../Command/ICommand.h"

class History
{
public:
    [[nodiscard]] bool CanUndo() const
    {
        return m_currentActionIndex > 0;
    }

    [[nodiscard]] bool CanRedo() const
    {
        return m_currentActionIndex < m_commands.size();
    }

    void Undo()
    {
        if (CanUndo())
        {
            m_commands[--m_currentActionIndex]->Unexecute();
        }
    }

    void Redo()
    {
        if (CanRedo())
        {
            m_commands[m_currentActionIndex++]->Execute();
        }
    }

    void AddAndExecuteCommand(std::unique_ptr<ICommand> command)
    {
        command->Execute();

        if (m_currentActionIndex < m_commands.size())
        {
            for (size_t i = m_currentActionIndex; i < m_commands.size(); ++i)
            {
               m_commands[i]->Destroy();
            }
            m_commands.erase(m_commands.begin() + m_currentActionIndex, m_commands.end());
        }

        m_commands.emplace_back(std::move(command));
        m_currentActionIndex++;

        if (m_commands.size() > MAX_COMMANDS_COUNT)
        {
            m_commands.erase(m_commands.begin());
            m_currentActionIndex--;
        }
    }

private:
    static constexpr const unsigned MAX_COMMANDS_COUNT = 10;

    std::vector<std::unique_ptr<ICommand>> m_commands;
    unsigned m_currentActionIndex = 0;
};