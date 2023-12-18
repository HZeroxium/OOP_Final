#pragma once

#include "uDataStorage.h"
#include "iDiscountCode.h"

/// @brief Singleton class for converting data between different types to string and vice versa.
class DataConverter
{
private:
    DataConverter() = default; ///< Private constructor of the Singleton Pattern

public: // Singleton Methods
    static DataConverter &getInstance();
    DataConverter(const DataConverter &) = delete;
    void operator=(const DataConverter &) = delete;
    ~DataConverter() = default;

public: // Data conversion methods
    static string convertProductToString(const Product &product);
    static string convertCustomerToString(const Customer &customer);
    static string convertStoreToString(const Store &store);
    static string convertDiscountCodeToString(const DiscountCode *discountCode);

    static Product convertStringToProduct(const string &sProduct);
    static Customer convertStringToCustomer(const string &sUser);
    static Date convertStringToDate(const string &sDate);
    static Store convertStringToStore(const string &sStore);
    static DiscountCode *convertStringToDiscountCode(const string &sDiscountCode);
};