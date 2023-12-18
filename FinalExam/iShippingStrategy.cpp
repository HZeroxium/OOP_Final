#include "iShippingStrategy.h"

double StandardShipping::calculateShippingCost(unsigned int orderAmount) const
{
    constexpr double STANDARD_SHIPPING_COST = 1000;
    return STANDARD_SHIPPING_COST * orderAmount;
}

double ExpressShipping::calculateShippingCost(unsigned int orderAmount) const
{
    constexpr double EXPRESS_SHIPPING_COST = 2000;
    return EXPRESS_SHIPPING_COST * orderAmount;
}