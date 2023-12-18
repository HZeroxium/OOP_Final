/**
 * @file iDiscountCode.h
 * @brief Strategy design pattern interface for discount codes
 *
 * This file contains the declaration of the iDiscountCode interface and its subclasses using the Strategy design pattern.
 *  for discount codes.
 */

#pragma once

#include "cOrder.h"

/// @brief Abstract class for discount codes using the Strategy design pattern
class DiscountCode
{
protected:
    string m_sCode;       ///< Code of the discount
    double m_dPercentage; ///< Percentage of discount
    double m_dMaxAmount;  ///< Maximum amount of discount

public:
    string getCode() const;
    void setCode(const string &code);
    double getPercentage() const;
    double getMaxAmount() const;
    virtual double applyDiscount(const Order &order) const = 0;
    virtual ~DiscountCode() = default;
};

/// @brief Concrete class for overall discount codes
class OverallDiscountCode : public DiscountCode
{
public:
    OverallDiscountCode(double percentage, double maxAmount);
    double applyDiscount(const Order &order) const override;
};

/// @brief Concrete class for category discount codes
class CategoryDiscountCode : public DiscountCode
{
private:
    string m_sCategory; ///< Category of products to apply the discount

public:
    string getCategory() const;
    CategoryDiscountCode(double percentage, double maxAmount, const string &category);
    double applyDiscount(const Order &order) const override;
};

/// @brief Concrete class for birthday discount codes
class BirthdayDiscountCode : public DiscountCode
{
public:
    BirthdayDiscountCode(double percentage, double maxAmount);
    double applyDiscount(const Order &order) const override;
};
