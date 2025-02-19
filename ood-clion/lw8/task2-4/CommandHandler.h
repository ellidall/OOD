#pragma once

#include <sstream>
#include "Menu.h"
#include "Multi/MultiGumballMachine.h"

class CommandHandler
{
public:
    CommandHandler(Menu& menu, MultiGumballMachine& multiGumballMachine)
            : m_menu(menu), m_multiGumballMachine(multiGumballMachine)
    {
        m_menu.AddItem("Help", "Help", [this](std::istream&) { m_menu.ShowInstructions(); });
        AddMenuItem("InsertQuarter", "InsertQuarter", &CommandHandler::InsertQuarter);
        AddMenuItem("EjectQuarter", "EjectQuarter", &CommandHandler::EjectQuarter);
        AddMenuItem("TurnCrank", "TurnCrank", &CommandHandler::TurnCrank);
        AddMenuItem("ToString", "ToString", &CommandHandler::ToString);
        AddMenuItem("Refill", "Refill", &CommandHandler::Fill);
    }

private:
    Menu& m_menu;
    MultiGumballMachine& m_multiGumballMachine;

    typedef void (CommandHandler::*MenuHandler)(std::istream& in);

    void AddMenuItem(const std::string& shortcut, const std::string& description, MenuHandler handler)
    {
        m_menu.AddItem(shortcut, description, bind(handler, this, std::placeholders::_1));
    }

    void InsertQuarter(std::istream& in)
    {
        m_multiGumballMachine.InsertQuarter();
    }

    void EjectQuarter(std::istream& in)
    {
        m_multiGumballMachine.EjectQuarter();
    }

    void TurnCrank(std::istream& in)
    {
        m_multiGumballMachine.TurnCrank();
    }

    void ToString(std::istream& in)
    {
        std::cout << m_multiGumballMachine.ToString() << std::endl;
    }

    void Fill(std::istream& in)
    {
        std::string m_countStr;
        in >> m_countStr;
        unsigned m_count = std::stoi(m_countStr);

        m_multiGumballMachine.Fill(m_count);
    }
};