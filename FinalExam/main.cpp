#include "uDataManager.h"
#include "cConsole.h"

int main()
{
    DataManager &dataManager = DataManager::getInstance();
    dataManager.loadData();

    Console &console = Console::getInstance();
    console.run();

    dataManager.saveData();

    return 0;
}