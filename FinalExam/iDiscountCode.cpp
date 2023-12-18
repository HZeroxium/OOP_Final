#include "iDiscountCode.h"
#include "iUserManagement.h"

//====================================================================================================================
//==================================== DISCOUNT CODE ==================================================================
//====================================================================================================================

string DiscountCode::getCode() const
{
    return m_sCode;
}

void DiscountCode::setCode(const string &code)
{
    m_sCode = code;
}

double DiscountCode::getPercentage() const
{
    return m_dPercentage;
}

double DiscountCode::getMaxAmount() const
{
    return m_dMaxAmount;
}

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
    const double dDiscount = std::min(order.getTotalPrice() * m_dPercentage, m_dMaxAmount);
    return dDiscount;
}

//====================================================================================================================
//==================================== CATEGORY DISCOUNT CODE ========================================================
//====================================================================================================================

string CategoryDiscountCode::getCategory() const
{
    return m_sCategory;
}

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
    const string orderDate = order.getOrderDate().toString();
    const string birthday = UserManager::getInstance().getCurrentUser()->getBirthDate().toString();
    if (orderDate.substr(0, 5) == birthday.substr(0, 5))
    {
        const double dDiscount = std::min(order.getTotalPrice() * m_dPercentage, m_dMaxAmount);
        return dDiscount;
    }
    return 0;
}