#pragma once

#include "cProduct.h"
#include "cOrder.h"
#include "cShoppingCart.h"
#include "cUser.h"
#include "cDate.h"
#include "iCustomerRank.h"
#include "iDiscountCode.h"
#include "cStore.h"
#include "iProductCategory.h"
#include "uDataConverter.h"

class DataManager
{
public:
    vector<Product> m_vProducts;                  ///< List of products
    vector<User *> m_vUsers;                      ///< List of users
    vector<Order> m_vOrders;                      ///< List of orders
    vector<Store> m_vStores;                      ///< List of stores
    vector<ProductCategory> m_vProductCategories; ///< List of product categories
    vector<DiscountCode *> m_vDiscountCodes;      ///< List of discount codes

private:
    DataManager(); ///< Private constructor of the Singleton Pattern

public: // Singleton Methods
    static DataManager &getInstance();
    DataManager(const DataManager &) = delete;
    void operator=(const DataManager &) = delete;
    ~DataManager() = default;

private: // Load data helpers
    bool loadProducts();
    bool loadUsers();
    bool loadOrders(const Customer &customer);
    bool loadStores();
    bool loadStoreProductList(Store &store);
    void loadProductCategories(ProductCategory &productCategory, std::ifstream &fin);
    bool loadProductCategories();
    bool loadDiscountCodes();

private: // Save data helpers
    bool saveProducts();
    bool saveUsers();
    bool saveOrders(const Customer &customer);
    bool saveStores();
    bool saveStoreProductList(const Store &store);
    void saveProductCategories(const ProductCategory &productCategory, std::ofstream &fout);
    bool saveProductCategories();
    bool saveDiscountCodes();

public: // Data management methods
    bool loadData();
    bool saveData();

public: // Singleton Getters
    DataConverter &getDataConverter();
    DataStorageSystem &getDataStorageSystem();

public: // Getters
    vector<Product> &getProducts();
    vector<User *> &getUsers();
    vector<Order> &getOrders();
    vector<Store> &getStores();
    vector<ProductCategory> &getProductCategories();
    vector<DiscountCode *> &getDiscountCodes();

public: // Accessors
    Product *getProduct(const string &sProductName) const;
    Product *getProductByCategory(const string &sProductName, const string &sProductCategoryName) const;
    User *getUser(const string &sUsername, const string &password) const;
    Store *getStore(const string &sStoreName) const;
    ProductCategory *getProductCategory(const string &sProductCategoryName) const;
    DiscountCode *getDiscountCode(const string &sDiscountCodeName) const;
};