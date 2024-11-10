#include "Document/CDocument.h"
#include "Menu/CMenu.h"
#include "CommandHandler.h"
#include <iostream>
#include <format>

int main()
{
    try
    {
        CMenu menu;
        CDocument document;
        CommandHandler commandHandler(menu, document);
        menu.Run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
