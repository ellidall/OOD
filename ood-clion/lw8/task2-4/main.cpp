#include <iostream>
#include "Multi/MultiGumballMachine.h"
#include "Menu.h"
#include "CommandHandler.h"

int main() {
    try
    {
        MultiGumballMachine multiGumballMachine1(1);
        Menu menu{};
        CommandHandler commandHandler(menu, multiGumballMachine1);

        menu.Run();
        menu.Exit();

        // Вывести сообщение об ошибке
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}