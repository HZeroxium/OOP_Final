#include "cStore.h"
#include <iostream>

//******************************************************************************************************
//************************************ CONSTRUCTORS & DESTRUCTOR ****************************************
//******************************************************************************************************

Store::Store()
{
    m_sName = "";
    m_joinDate = Date();
}

Store::Store(const string &sName, const Date &joinDate)
{
    m_sName = sName;
    m_joinDate = joinDate;
}

Store::Store(const Store &other)
{
    m_sName = other.m_sName;
    m_joinDate = other.m_joinDate;
    m_vProducts = other.m_vProducts;
}

Store::~Store()
{
    m_vProducts.clear();
}

//******************************************************************************************************
//********************************************** GETTERS ***********************************************
//******************************************************************************************************

string Store::getName() const
{
    return m_sName;
}

Date Store::getJoinDate() const
{
    return m_joinDate;
}

vector<Product *> &Store::getProducts()
{
    return m_vProducts;
}

//******************************************************************************************************
//********************************************** SETTERS ***********************************************
//******************************************************************************************************

void Store::setName(const string &sName)
{
    m_sName = sName;
}

void Store::setJoinDate(const Date &joinDate)
{
    m_joinDate = joinDate;
}

//******************************************************************************************************
//********************************************** DISPLAY ***********************************************
//******************************************************************************************************

//******************************************************************************************************
//********************************************** ADD & REMOVE *******************************************
//******************************************************************************************************

bool Store::addProduct(Product *pProduct)
{
    // Find if the product already exists
    for (auto it = m_vProducts.begin(); it != m_vProducts.end(); ++it)
    {
        if ((*it)->getName() == pProduct->getName())
        {
            // If it does, add the quantity of the new product to the existing product
            const unsigned int uiOldQuantity = (*it)->getQuantity();
            const unsigned int uiNewQuantity = pProduct->getQuantity();
            (*it)->setQuantity(uiOldQuantity + uiNewQuantity);
            return true;
        }
    }

    // If it doesn't, add the product to the store
    m_vProducts.push_back(pProduct);
}

bool Store::removeProduct(Product *pProduct)
{
    // Find if the product exists
    for (auto it = m_vProducts.begin(); it != m_vProducts.end(); ++it)
    {
        if ((*it)->getName() == pProduct->getName())
        {
            m_vProducts.erase(it);
            return true;
        }
    }

    // If it doesn't, return false
    std::cerr << "Product " << pProduct->getName() << " does not exist in store!" << std::endl;
    return false;
}
