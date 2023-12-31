#include "cProduct.h"
#include <iostream>

//=====================================================================================================================
//==================================== FLASH SALE =====================================================================
//=====================================================================================================================

//*********************************************************************************************************************
//************************************** OBSERVER METHODS *************************************************************
//*********************************************************************************************************************

void FlashSale::addObserver(Observer *observer)
{
    m_vObservers.push_back(observer);
}

void FlashSale::removeObserver(Observer *observer)
{
    // Find the observer
    for (auto it = m_vObservers.begin(); it != m_vObservers.end(); ++it)
    {
        if (*it == observer)
        {
            m_vObservers.erase(it);
            break;
        }
    }
}

void FlashSale::notifyObservers()
{
    for (const auto observer : m_vObservers)
    {
        observer->update(this->m_bIsOnFlashSale);
    }
}

//********************************************************************************************************************
//************************************** FLASH SALE METHODS **********************************************************
//********************************************************************************************************************

void FlashSale::setFlashSaleStatus(Product *product, bool bIsOnFlashSale)
{
		product->setFlashSale(bIsOnFlashSale);
}

void FlashSale::setFlashSaleStatus(bool bIsOnFlashSale)
{
    this->m_bIsOnFlashSale = bIsOnFlashSale;
    notifyObservers();
}

//=====================================================================================================================
//======================================= PRODUCT =====================================================================
//=====================================================================================================================

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
    m_vReviews = vector<Review>();
}

Product::Product(const Product &other)
{
    m_sID = other.m_sID;
    m_sName = other.m_sName;
    m_sCategory = other.m_sCategory;
    m_dPrice = other.m_dPrice;
    m_uiQuantity = other.m_uiQuantity;
    m_bIsOnFlashSale = other.m_bIsOnFlashSale;
    m_vReviews = other.m_vReviews;
}

Product::~Product() = default;

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

vector<Review> Product::getReviews() const
{
    return m_vReviews;
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

void Product::setReviews(const vector<Review> &vReviews)
{
    m_vReviews = vReviews;
}

//******************************************************************************************************
//********************************************** DISPLAY ***********************************************
//******************************************************************************************************

//******************************************************************************************************
//********************************************** METHODS ************************************************
//******************************************************************************************************

void Product::update(bool bFlashSale)
{
    const bool isSame = (m_bIsOnFlashSale == bFlashSale);
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

void Product::addReview(const Review &review)
{
    m_vReviews.push_back(review);
}
