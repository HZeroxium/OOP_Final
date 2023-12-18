#pragma once

#include "iPaymentMethod.h"

/// @brief Payment method factory interface
class PaymentMethodFactory
{
public:
    virtual PaymentMethod *createPaymentMethod() const = 0;
    virtual ~PaymentMethodFactory() = default;
};

/// @brief Credit card payment method factory
class CreditCardFactory : public PaymentMethodFactory
{
public:
    PaymentMethod *createPaymentMethod() const override;
};

/// @brief Momo payment method factory
class MomoPaymentFactory : public PaymentMethodFactory
{
public:
    PaymentMethod *createPaymentMethod() const override;
};