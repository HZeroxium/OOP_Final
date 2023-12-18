#include "iCustomerRank.h"

constexpr double BRONZE_DISCOUNT = 0.01;
constexpr double SILVER_DISCOUNT = 0.02;
constexpr double GOLD_DISCOUNT = 0.04;

double BronzeCustomerRank::applyDiscount(double price) const
{
    return price * (1 - BRONZE_DISCOUNT);
}

double SilverCustomerRank::applyDiscount(double price) const
{
    return price * (1 - SILVER_DISCOUNT);
}

double GoldCustomerRank::applyDiscount(double price) const
{
    return price * (1 - GOLD_DISCOUNT);
}