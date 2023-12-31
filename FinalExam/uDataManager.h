#pragma once

#include "cProduct.h"
#include "cOrder.h"
#include "cUser.h"
#include "cDate.h"
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
    DataManager() = default; ///< Private constructor of the Singleton Pattern

public: // Singleton Methods
    static DataManager &getInstance();
    DataManager(const DataManager &) = delete;
    void operator=(const DataManager &) = delete;
    ~DataManager();

private: // Load data helpers
    bool loadProducts();
    bool loadUsers();
    bool loadOrders(const Customer &customer);
    bool loadStores();
    static bool loadStoreProductList(Store &store);
    static void loadProductCategories(ProductCategory &productCategory, std::ifstream &fin);
    static bool loadProductCategories();
    bool loadDiscountCodes();
    static bool loadReviews(Product &product);

private: // Save data helpers
    bool saveProducts() const;
    bool saveUsers() const;
    static bool saveOrders(const Customer &customer);
    bool saveStores() const;
    static bool saveStoreProductList(const Store &store);
    static void saveProductCategories(const ProductCategory &productCategory, std::ofstream &fout);
    bool saveProductCategories() const;
    bool saveDiscountCodes() const;
    static bool saveReviews(const Product &product);

public: // Data management methods
    bool loadData();
    bool saveData() const;

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