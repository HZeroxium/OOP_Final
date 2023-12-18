#pragma once

#include "cDate.h"

/// @brief Payment method interface
class PaymentMethod
{
public:
    virtual void processPayment(double amount) const = 0;
    virtual ~PaymentMethod() = default;
};

/// @brief Credit card payment method
class CreditCardPayment : public PaymentMethod
{
private:
    string m_sCardNumber;  ///< Card number of the credit card
    string m_sCVC;         ///< CVC of the credit card
    string m_sName;        ///< Name of the credit card
    Date m_expirationDate; ///< Expiration date of the credit card

public: // Constructors & Destructor
    CreditCardPayment();
    CreditCardPayment(const string &sCardNumber, const string &sCVC, const string &sName, const Date &expirationDate);
    CreditCardPayment(const CreditCardPayment &);
    ~CreditCardPayment() = default;

public: // Getters
    string getCardNumber() const;
    string getCVC() const;
    string getName() const;
    Date getExpirationDate() const;

public: // Setters
    void setCardNumber(const string &sCardNumber);
    void setCVC(const string &sCVC);
    void setName(const string &sName);
    void setExpirationDate(const Date &expirationDate);

public: // Methods
    void processPayment(double amount) const override;
};

/// @brief Momo payment method
class MomoPayment : public PaymentMethod
{
private:
    string m_sPhoneNumber; ///< Phone number of the momo account

public: // Constructors & Destructor
    MomoPayment();
    MomoPayment(const string &sPhoneNumber);
    MomoPayment(const MomoPayment &);
    ~MomoPayment() = default;

public: // Getters
    string getPhoneNumber() const;

public: // Setters
    void setPhoneNumber(const string &sPhoneNumber);

public: // Methods
    void processPayment(double amount) const override;
};
