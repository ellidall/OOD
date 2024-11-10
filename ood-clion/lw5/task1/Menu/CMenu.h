#pragma once

#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using Command = std::function<void(std::istringstream&)>;

class CMenu
{
public:
    void AddItem(
            const std::string& shortcut,
            const std::string& description,
            const Command& command
    )
    {
        m_items.emplace_back(shortcut, description, command);
    }

    void Run()
    {
        ShowInstructions();

        std::string command;
        while (std::cout << ">"
               && getline(std::cin, command)
               && ExecuteCommand(command))
        {
        }
    }

    void ShowInstructions()
    {
        std::cout << "Commands list:\n";
        for (auto& item : m_items)
        {
            std::cout << "  " << item.shortcut << ". " << item.description << std::endl;
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
        std::string shortcut;
        iss >> shortcut;

        m_exit = false;

        const auto it = std::ranges::find_if(m_items, [&](const Item& item) {
            return item.shortcut == shortcut;
        });

        if (it == m_items.end())
        {
            std::cout << "Unknown command" << std::endl;
            return !m_exit;
        }

        try
        {
            it->command(iss);
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
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

    std::vector<Item> m_items{};
    bool m_exit = false;
};