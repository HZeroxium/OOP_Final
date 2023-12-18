/**
 * @file cShoppingCart.h
 * @brief Shopping cart class using Singleton Pattern and Observer Pattern
 */

#pragma once

#include "cProduct.h"
#include "cUser.h"
#include <vector>
#include "uDataManager.h"

using std::pair;
using std::vector;

/// @brief Iterator interface using the Iterator design pattern
class ProductIterator
{
public:
    virtual ~ProductIterator() = default;
    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool hasNext() const = 0;
    virtual Product* currentItem() const = 0;
};

/// @brief Collection interface using the Iterator design pattern
class ProductCollection
{
public:
    virtual ~ProductCollection() = default;
    virtual ProductIterator* createIterator() = 0;
    virtual void addProduct(Product* product, unsigned int quantity) = 0;
    virtual void removeProduct(Product* product) = 0;
    virtual size_t getProductCount() const = 0;
};

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
    ~ShoppingCart() override = default;

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

/// @brief Concrete implementation of ProductIterator class
class ShoppingCartIterator : public ProductIterator
{
private:
    ShoppingCart* m_pShoppingCart;
    size_t m_uiCurrentIndex;

public:
    ShoppingCartIterator(ShoppingCart* pShoppingCart);
    void first() override;
    void next() override;
    bool hasNext() const override;
    [[nodiscard]] Product* currentItem() const override;
};
