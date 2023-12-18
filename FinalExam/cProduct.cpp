#include "cProduct.h"
#include <iostream>

//******************************************************************************************************
//************************************ CONSTRUCTORS & DESTRUCTOR ****************************************
//******************************************************************************************************

Product::Product()
{
    m_sName = "";
    m_sCategory = "";
    m_dPrice = 0;
    m_uiQuantity = 0;
    m_bIsOnFlashSale = false;
}

Product::Product(const string &sID, const string &sName, const string &sCategory, double dPrice, unsigned int uiQuantity, bool bIsOnFlashSale)
{
    m_sID = sID;
    m_sName = sName;
    m_sCategory = sCategory;
    m_dPrice = dPrice;
    m_uiQuantity = uiQuantity;
    m_bIsOnFlashSale = bIsOnFlashSale;
}

Product::Product(const Product &other)
{
    m_sID = other.m_sID;
    m_sName = other.m_sName;
    m_sCategory = other.m_sCategory;
    m_dPrice = other.m_dPrice;
    m_uiQuantity = other.m_uiQuantity;
    m_bIsOnFlashSale = other.m_bIsOnFlashSale;
}

Product::~Product()
{
}

//******************************************************************************************************
//********************************************** GETTERS ***********************************************
//******************************************************************************************************

string Product::getID() const
{
    return m_sID;
}

string Product::getName() const
{
    return m_sName;
}

string Product::getCategory() const
{
    return m_sCategory;
}

double Product::getPrice() const
{
    return m_dPrice;
}

unsigned int Product::getQuantity() const
{
    return m_uiQuantity;
}

bool Product::getFlashSaleStatus() const
{
    return m_bIsOnFlashSale;
}

//******************************************************************************************************
//********************************************** SETTERS ***********************************************
//******************************************************************************************************

void Product::setID(const string &sID)
{
    m_sID = sID;
}

void Product::setName(const string &sName)
{
    m_sName = sName;
}

void Product::setCategory(const string &sCategory)
{
    m_sCategory = sCategory;
}

void Product::setPrice(double dPrice)
{
    m_dPrice = dPrice;
}

void Product::setQuantity(unsigned int uiQuantity)
{
    m_uiQuantity = uiQuantity;
}

void Product::setFlashSale(bool bIsOnFlashSale)
{
    if (m_bIsOnFlashSale != bIsOnFlashSale)
    {
        update(bIsOnFlashSale);
    }
}

//******************************************************************************************************
//********************************************** DISPLAY ***********************************************
//******************************************************************************************************

//******************************************************************************************************
//********************************************** METHODS ************************************************
//******************************************************************************************************

void Product::update(bool bFlashSale)
{
    bool isSame = (m_bIsOnFlashSale == bFlashSale);
    if (!isSame)
    {
        m_bIsOnFlashSale = bFlashSale;
        if (m_bIsOnFlashSale)
        {
            const double newPrice = m_dPrice * (1 - FlashSale::FLASH_SALE_PERCENTAGE);
            setPrice(newPrice);
            std::cout << "!!! FLASH SALE !!! Price of " << m_sName << " is now " << m_dPrice << " VND" << std::endl;
        }
        else
        {
            const double newPrice = m_dPrice / (1 - FlashSale::FLASH_SALE_PERCENTAGE);
            setPrice(newPrice);
            std::cout << "!!! FLASH SALE is over !!! Price of " << m_sName << " is now " << m_dPrice << " VND" << std::endl;
        }
    }
}