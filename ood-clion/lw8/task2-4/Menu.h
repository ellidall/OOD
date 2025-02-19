#pragma once

#include <iostream>
#include <functional>
#include <sstream>

class Menu
{
public:
    typedef std::function<void(std::istream& args)> Command;

    void AddItem(const std::string& shortcut, const std::string& description, const Command& command)
    {
        m_items.emplace_back(shortcut, description, command);
    }

    void Run()
    {
        ShowInstructions();

        std::string command;
        while ((std::cout << ">")
               && getline(std::cin, command)
               && !command.empty()
               && ExecuteCommand(command))
        {
        }
    }

    void ShowInstructions() const
    {
        std::cout << "Commands list:\n";
        for (auto& item : m_items)
        {
            std::cout << "  " << item.shortcut << ": " << item.description << "\n";
        }
    }

    void Exit()
    {
        m_exit = true;
    }

private:
    bool ExecuteCommand(const std::string& command)
    {
        std::istringstream iss(command);
        std::string name;
        iss >> name;

        m_exit = false;
        auto it = std::find_if(m_items.begin(), m_items.end(), [&](const Item& item) {
            return item.shortcut == name;
        });

        if (it != m_items.end())
        {
            it->command(iss);
        }
        else
        {
            std::cout << "Unknown command\n";
        }
        return !m_exit;
    }

    struct Item
    {
        Item(std::string shortcut, std::string description, Command command)
                : shortcut(std::move(shortcut)), description(std::move(description)), command(std::move(command))
        {}

        std::string shortcut;
        std::string description;
        Command command;
    };

    std::vector<Item> m_items = {};
    bool m_exit = false;
};