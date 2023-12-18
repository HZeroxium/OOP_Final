#pragma once

#include "cProduct.h"
#include "cShoppingCart.h"
/// @brief Iterator interface using the Iterator design pattern
class ProductIterator
{
public:
    virtual ~ProductIterator() = default;
    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool hasNext() = 0;
    virtual Product *currentItem() const = 0;
};

/// @brief Collection interface using the Iterator design pattern
class ProductCollection
{
public:
    virtual ~ProductCollection() = default;
    virtual ProductIterator *createIterator() = 0;
    virtual void addProduct(Product *product, unsigned int quantity) = 0;
    virtual void removeProduct(Product *product) = 0;
    virtual size_t getProductCount() const = 0;
};

/// @brief Concrete implementation of ProductIterator class
class ShoppingCartIterator : public ProductIterator
{
private:
    const ShoppingCart *m_pShoppingCart;
    size_t m_uiCurrentIndex;

public:
    ShoppingCartIterator(const ShoppingCart *pShoppingCart);
    void first() override;
    void next() override;
    bool hasNext() override;
    Product *currentItem() const override;
};