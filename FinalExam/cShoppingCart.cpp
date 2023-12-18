#include "cShoppingCart.h"
#include <fstream>
#include <iostream>
#include <sstream>

//******************************************************************************************************
//************************************ SINGLETON PATTERN METHODS ****************************************
//******************************************************************************************************

ShoppingCart &ShoppingCart::getInstance()
{
    static ShoppingCart instance;
    return instance;
}

//******************************************************************************************************
//************************************ SHOPPING CART METHODS *******************************************
//******************************************************************************************************

ProductIterator *ShoppingCart::createIterator()
{
    return new ShoppingCartIterator(this);
}

void ShoppingCart::addProduct(Product *pProduct, unsigned int uiQuantity)
{
    // Check if the product is already in the shopping cart
    for (auto &product : m_vProducts)
    {
        if (product.first->getName() == pProduct->getName())
        {
            product.second += uiQuantity;
            return;
        }
    }

    // If the product is not in the shopping cart, add it
    m_vProducts.push_back(std::make_pair(pProduct, uiQuantity));
}

void ShoppingCart::removeProduct(Product *pProduct)
{
    // Find if the product exists
    for (auto it = m_vProducts.begin(); it != m_vProducts.end(); ++it)
    {
        if ((*it).first->getName() == pProduct->getName())
        {
            m_vProducts.erase(it);
            return;
        }
    }

    // If it doesn't, return false
    std::cerr << "Product " << pProduct->getName() << " does not exist in shopping cart!" << std::endl;
}

size_t ShoppingCart::getProductCount() const
{
    return m_vProducts.size();
}

Product *ShoppingCart::getProductAtIndex(size_t index) const
{
    return m_vProducts[index].first;
}

const vector<pair<Product *, unsigned int>> &ShoppingCart::getProducts() const
{
    return m_vProducts;
}

Product *ShoppingCart::findProduct(const string &sName) const
{
    for (auto &product : m_vProducts)
    {
        if (product.first->getName() == sName)
        {
            return product.first;
        }
    }

    return nullptr;
}

void ShoppingCart::increaseQuantity(const string &sName, unsigned int uiQuantity)
{
    for (auto &product : m_vProducts)
    {
        if (product.first->getName() == sName)
        {
            product.second += uiQuantity;
            return;
        }
    }
}

void ShoppingCart::decreaseQuantity(const string &sName, unsigned int uiQuantity)
{
    for (auto &product : m_vProducts)
    {
        if (product.first->getName() == sName)
        {
            product.second -= uiQuantity;
            return;
        }
    }
}

bool ShoppingCart::loadCurrentUsersShoppingCart(User *pUser)
{
    // Clear the current shopping cart
    m_vProducts.clear();

    // Check if the user is customer
    Customer *pCustomer = dynamic_cast<Customer *>(pUser);
    if (pCustomer == nullptr)
    {
        return false;
    }

    const string sCartFilePath = DataStorageSystem::getInstance().getShoppingCartFilePath(*pCustomer);
    std::ifstream fin(sCartFilePath);

    // Check if the file exists
    if (!fin.is_open())
    {
        return;
        std::cerr << "Cannot open file " << sCartFilePath << std::endl;
    }

    // Read the file
    string sLine;
    while (std::getline(fin, sLine))
    {
        std::stringstream ss(sLine);
        string sName;
        unsigned int uiQuantity;
        std::getline(ss, sName, ',');
        ss >> uiQuantity;

        Product *pProduct = DataManager::getInstance().getProduct(sName);
        if (pProduct != nullptr)
        {
            m_vProducts.push_back(std::make_pair(pProduct, uiQuantity));
        }

        ss.clear();
    }

    fin.close();
    return true;
}