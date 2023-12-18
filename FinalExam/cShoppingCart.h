/**
 * @file cShoppingCart.h
 * @brief Shopping cart class using Singleton Pattern and Observer Pattern
 */

#pragma once

#include "cProduct.h"
#include "iProductIterator.h"
#include "cUser.h"
#include <vector>
#include "uDataManager.h"

using std::pair;
using std::vector;

/// @brief Shopping cart class using Singleton Pattern and Observer Pattern
class ShoppingCart : public ProductCollection
{
private:
    vector<pair<Product *, unsigned int>> m_vProducts; ///< List of products in the shopping cart
    ShoppingCart() = default;                          ///< Private constructor of the Singleton Pattern

public: // Singleton Methods
    static ShoppingCart &getInstance();
    ShoppingCart(const ShoppingCart &) = delete;
    void operator=(const ShoppingCart &) = delete;
    ~ShoppingCart() = default;

public: // Shopping cart methods
    ProductIterator *createIterator() override;
    void addProduct(Product *pProduct, unsigned int uiQuantity) override;
    void removeProduct(Product *pProduct) override;
    size_t getProductCount() const override;
    Product *getProductAtIndex(size_t index) const;

    const vector<pair<Product *, unsigned int>> &getProducts() const;

    Product *findProduct(const string &sName) const;
    void increaseQuantity(const string &sName, unsigned int uiQuantity);
    void decreaseQuantity(const string &sName, unsigned int uiQuantity);

    bool loadCurrentUsersShoppingCart(User *pUser);
};
