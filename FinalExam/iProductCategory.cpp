#include "iProductCategory.h"
#include <iostream>

//======================================================================================================
//======================================== PRODUCT CATEGORY ============================================

ProductCategory::ProductCategory(const string &sName)
{
    m_sName = sName;
}

string ProductCategory::getName() const
{
    return m_sName;
}

void ProductCategory::setName(const string &sName)
{
    m_sName = sName;
}

//======================================================================================================
//======================================== LEAF PRODUCT CATEGORY =======================================
//======================================================================================================

LeafProductCategory::LeafProductCategory(const string &sCategoryName) : ProductCategory(sCategoryName)
{
}

LeafProductCategory::~LeafProductCategory()
{
    m_vProducts.clear();
}

void LeafProductCategory::display() const
{
    // Display category name
}

//======================================================================================================
//==================================== COMPOSITE PRODUCT CATEGORY ======================================
//======================================================================================================

CompositeProductCategory::CompositeProductCategory(const string &sCategoryName) : ProductCategory(sCategoryName)
{
}

CompositeProductCategory::~CompositeProductCategory()
{
    m_vProductCategories.clear();
}

void CompositeProductCategory::display() const
{
    // Display category name
}

bool CompositeProductCategory::addSubCategory(ProductCategory *pProductCategory)
{
    // Find if the category already exists
    for (auto it = m_vProductCategories.begin(); it != m_vProductCategories.end(); ++it)
    {
        if ((*it)->getName() == pProductCategory->getName())
        {
            std::cerr << "Category " << pProductCategory->getName() << " already exists!" << std::endl;
            return false;
        }
    }

    // Add the category
    m_vProductCategories.push_back(pProductCategory);
    return true;
}

bool CompositeProductCategory::removeSubCategory(const ProductCategory *pProductCategory)
{
    // Find if the category exists
    for (auto it = m_vProductCategories.begin(); it != m_vProductCategories.end(); ++it)
    {
        if ((*it)->getName() == pProductCategory->getName())
        {
            m_vProductCategories.erase(it);
            return true;
        }
    }

    std::cerr << "Category " << pProductCategory->getName() << " does not exist!" << std::endl;
    return false;
}
