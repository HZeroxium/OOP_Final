/**
 * @file ProductCategory.h
 *
 * @brief Definition of the ProductCategory class using Composite Pattern representing a product category in the store inventory system
 *
 */

#pragma once

#include "cProduct.h"
#include <vector>
#include <memory>

using std::unique_ptr;
using std::vector;

/// @brief Component class of the Composite Pattern
class ProductCategory
{
protected:
    string m_sName;                ///< Name of the product category
    vector<Product *> m_vProducts; ///< List of products in the category

public:
    void setName(const string &sName);
    string getName() const;
    virtual ~ProductCategory() = default;
    virtual void display() const = 0;
};

/// @brief Leaf class of the Composite Pattern
class LeafProductCategory : public ProductCategory
{
public: // Constructors & Destructor
    LeafProductCategory(const string &sName);
    ~LeafProductCategory();

public: // Display
    void display() const override;
};

/// @brief Composite class of the Composite Pattern
class CompositeProductCategory : public ProductCategory
{
private:
    vector<ProductCategory *> m_vProductCategories; ///< List of product categories in the category

public: // Constructors & Destructor
    CompositeProductCategory(const string &sName);
    ~CompositeProductCategory();

public: // Display
    const vector<ProductCategory *> &getSubCategories() const;
    void display() const override;

public: // Add & Remove
    bool addSubCategory(ProductCategory *pProductCategory);
    bool removeSubCategory(ProductCategory *pProductCategory);
};