#include "uDataStorage.h"

//******************************************************************************************************
//************************************ SINGLETON METHODS ***********************************************
//******************************************************************************************************

DataStorageSystem &DataStorageSystem::getInstance()
{
    static DataStorageSystem instance;
    return instance;
}

//******************************************************************************************************
//************************************ DIRECTORY METHODS ***********************************************
//******************************************************************************************************

string DataStorageSystem::getDataStorageDirectoryPath()
{
    return "./data";
}

string DataStorageSystem::getDiscountCodeDirectoryPath()
{
    return getDataStorageDirectoryPath() + "/discount_code";
}

string DataStorageSystem::getProductDirectoryPath()
{
    return getDataStorageDirectoryPath() + "/product";
}

string DataStorageSystem::getStoreDirectoryPath()
{
    return getDataStorageDirectoryPath() + "/store";
}

string DataStorageSystem::getUserDirectoryPath()
{
    return getDataStorageDirectoryPath() + "/user";
}

string DataStorageSystem::getCustomerDirectoryPath()
{
    return getUserDirectoryPath() + "/customer";
}

string DataStorageSystem::getSpecificStoreDirectoryPath(const Store &store)
{
    return getStoreDirectoryPath() + "/" + store.getName();
}

string DataStorageSystem::getSpecificCustomerDirectoryPath(const Customer &customer)
{
    return getCustomerDirectoryPath() + "/" + customer.getUsername();
}

string DataStorageSystem::getCustomerOrderDirectoryPath(const Customer &customer)
{
    return getSpecificCustomerDirectoryPath(customer) + "/order";
}

//******************************************************************************************************
//************************************ FILE METHODS ***************************************************
//******************************************************************************************************

string DataStorageSystem::getDiscountCodeListFilePath()
{
    return getDiscountCodeDirectoryPath() + "/discount_code_list.txt";
}

string DataStorageSystem::getProductListFilePath()
{
    return getProductDirectoryPath() + "/product_list.txt";
}

string DataStorageSystem::getCategoryListFilePath()
{
    return getProductDirectoryPath() + "/category_list.txt";
}

string DataStorageSystem::getStoreListFilePath()
{
    return getStoreDirectoryPath() + "/store_list.txt";
}

string DataStorageSystem::getUserListFilePath()
{
    return getUserDirectoryPath() + "/user_list.txt";
}

string DataStorageSystem::getSpecificProductListFilePath(const Store &store)
{
    return getSpecificStoreDirectoryPath(store) + "/product_list.txt";
}

string DataStorageSystem::getShoppingCartFilePath(const Customer &customer)
{
    return getSpecificCustomerDirectoryPath(customer) + "/shopping_cart.txt";
}

string DataStorageSystem::getCustomerOrderFilePath(const Customer &customer, const Order &order)
{
    return getCustomerOrderDirectoryPath(customer) + "/" + order.getOrderCode() + ".txt";
}
