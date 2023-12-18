/**
 * @file ProductBuilder.h
 * @brief Definition of the ProductBuilder class representing a builder of a product in the store inventory system using Builder Pattern
 */

#pragma once

#include "cProduct.h"

/// @brief Builder interface of the Builder Pattern
class ProductBuilder
{
public:
    virtual ~ProductBuilder() = default;
    virtual void buildName(const string &sName) = 0;
    virtual void buildCategory(const string &sCategory) = 0;
    virtual void buildPrice(double dPrice) = 0;
    virtual void buildQuantity(unsigned int uiQuantity) = 0;
    virtual Product getProduct() = 0;
};

/// @brief Concrete builder class of the Builder Pattern
class ConcreteProductBuilder : public ProductBuilder
{
private:
    Product m_product; ///< Product to build

public:
    void buildName(const string &sName) override;
    void buildCategory(const string &sCategory) override;
    void buildPrice(double dPrice) override;
    void buildQuantity(unsigned int uiQuantity) override;
    Product getProduct() override;
};

/// @brief Director class of the Builder Pattern
class ProductDirector
{
private:
    ProductBuilder *m_pProductBuilder; ///< Product builder

public:
    ProductDirector(ProductBuilder *pProductBuilder);
    void makeProduct(const string &sName, const string &sCategory, double dPrice, unsigned int uiQuantity);
    Product getProduct();
};
