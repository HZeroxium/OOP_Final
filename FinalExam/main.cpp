#include "uDataManager.h"
#include "cConsole.h"

int main()
{
    // Load all data
    DataManager::getInstance().loadData();

    // Run the console
    Console::getInstance().run();

    // Save all data
    DataManager::getInstance().saveData();

    return 0;
}