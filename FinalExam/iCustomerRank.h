#pragma once

#include <string>
using std::string;

enum CustomerRankType
{
    REGULAR,
    BRONZE,
    SILVER,
    GOLD
};

/// @brief Abstract class for customer ranks using the Strategy design pattern
class CustomerRank
{
public:
    void getRankName() const;
    virtual double applyDiscount(double price) const = 0;
    virtual ~CustomerRank() = default;
};

/// @brief Concrete class for Regular Customer rank
class RegularCustomerRank : public CustomerRank
{
public:
    double applyDiscount(double price) const override;
};

/// @brief Concrete class for Bronze Customer rank
class BronzeCustomerRank : public CustomerRank
{
public:
    double applyDiscount(double price) const override;
};

/// @brief Concrete class for Silver Customer rank
class SilverCustomerRank : public CustomerRank
{
public:
    double applyDiscount(double price) const override;
};

/// @brief Concrete class for Gold Customer rank
class GoldCustomerRank : public CustomerRank
{
public:
    double applyDiscount(double price) const override;
};
