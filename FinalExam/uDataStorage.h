#pragma once

#include "cProduct.h"
#include "cUser.h"
#include "cOrder.h"
#include "cDate.h"
#include "cShoppingCart.h"
#include "cStore.h"
#include "iProductCategory.h"

class DataStorageSystem
{
private:
    DataStorageSystem() = default; ///< Private constructor of the Singleton Pattern

public: // Singleton Methods
    static DataStorageSystem &getInstance();
    DataStorageSystem(const DataStorageSystem &) = delete;
    void operator=(const DataStorageSystem &) = delete;
    ~DataStorageSystem() = default;

public: // Directory methods
    static string getDataStorageDirectoryPath();
    static string getDiscountCodeDirectoryPath();
    static string getProductDirectoryPath();
    static string getStoreDirectoryPath();
    static string getUserDirectoryPath();
    static string getCustomerDirectoryPath();

    static string getSpecificStoreDirectoryPath(const Store &store);
    static string getSpecificCustomerDirectoryPath(const Customer &customer);
    static string getCustomerOrderDirectoryPath(const Customer &customer);

public: // File methods
    static string getDiscountCodeListFilePath();
    static string getProductListFilePath();
    static string getCategoryListFilePath();
    static string getStoreListFilePath();
    static string getUserListFilePath();

    static string getSpecificProductListFilePath(const Store &store);
    static string getShoppingCartFilePath(const Customer &customer);
    static string getCustomerOrderFilePath(const Customer &customer, const Order &order);
};