#include "iPaymentMethodFactory.h"

PaymentMethod *CreditCardFactory::createPaymentMethod() const
{
    return new CreditCardPayment();
}

PaymentMethod *MomoPaymentFactory::createPaymentMethod() const
{
    return new MomoPayment();
}