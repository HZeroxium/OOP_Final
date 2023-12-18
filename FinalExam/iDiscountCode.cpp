#include "iDiscountCode.h"
#include "iUserManagement.h"

//====================================================================================================================
//==================================== OVERALL DISCOUNT CODE =========================================================
//====================================================================================================================

OverallDiscountCode::OverallDiscountCode(double percentage, double maxAmount)
{
    m_dPercentage = percentage;
    m_dMaxAmount = maxAmount;
}

double OverallDiscountCode::applyDiscount(const Order &order) const
{
    double dDiscount = std::min(order.getTotalPrice() * m_dPercentage, m_dMaxAmount);
    return dDiscount;
}

//====================================================================================================================
//==================================== CATEGORY DISCOUNT CODE ========================================================
//====================================================================================================================

CategoryDiscountCode::CategoryDiscountCode(double percentage, double maxAmount, const string &category)
{
    m_dPercentage = percentage;
    m_dMaxAmount = maxAmount;
    m_sCategory = category;
}

double CategoryDiscountCode::applyDiscount(const Order &order) const
{
    double dDiscount = 0;
    for (const auto &[product, quantity] : order.getProducts())
    {
        if (product->getCategory() == m_sCategory)
        {
            dDiscount += product->getPrice() * quantity * m_dPercentage;
        }
    }
    dDiscount = std::min(dDiscount, m_dMaxAmount);
    return dDiscount;
}

//====================================================================================================================
//==================================== BIRTHDAY DISCOUNT CODE ========================================================
//====================================================================================================================

BirthdayDiscountCode::BirthdayDiscountCode(double percentage, double maxAmount)
{
    m_dPercentage = percentage;
    m_dMaxAmount = maxAmount;
}

double BirthdayDiscountCode::applyDiscount(const Order &order) const
{
    string orderDate = order.getOrderDate().toString();
    string birthday = UserManager::getInstance().getCurrentUser()->getBirthDate().toString();
    if (orderDate.substr(0, 5) == birthday.substr(0, 5))
    {
        double dDiscount = std::min(order.getTotalPrice() * m_dPercentage, m_dMaxAmount);
        return dDiscount;
    }
}