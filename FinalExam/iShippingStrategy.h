/**
 * @file iShippingStrategy.h
 * @brief This file contains the declaration of the iShippingStrategy interface and its subclasses using the Strategy design pattern.
 */

#pragma once

/// @brief Shipping strategy interface using the Strategy design pattern
class ShippingStrategy
{
public:
    virtual double calculateShippingCost(unsigned int orderAmount) const = 0;
    virtual ~ShippingStrategy() = default;
};

/// @brief Concrete class for Standard shipping strategy
class StandardShipping : public ShippingStrategy
{
public:
    double calculateShippingCost(unsigned int orderAmount) const override;
};

/// @brief Concrete class for Express shipping strategy
class ExpressShipping : public ShippingStrategy
{
public:
    double calculateShippingCost(unsigned int orderAmount) const override;
};

/// @brief Enum for shipping strategy type
enum ShippingStrategyType
{
    STANDARD,
    EXPRESS
};