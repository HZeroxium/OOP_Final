#include "iPaymentMethod.h"
#include <iostream>

//=================================================================================================
//======================================= CREDIT CARD PAYMENT =====================================
//=================================================================================================

//*************************************************************************************************
//******************************** CONSTRUCTORS & DESTRUCTOR **************************************
//*************************************************************************************************

CreditCardPayment::CreditCardPayment()
{
    m_sCardNumber = "";
    m_sCVC = "";
    m_sName = "";
    m_expirationDate = Date();
}

CreditCardPayment::CreditCardPayment(const string &sCardNumber, const string &sCVC, const string &sName, const Date &expirationDate)
{
    m_sCardNumber = sCardNumber;
    m_sCVC = sCVC;
    m_sName = sName;
    m_expirationDate = expirationDate;
}

CreditCardPayment::CreditCardPayment(const CreditCardPayment &other)
{
    m_sCardNumber = other.m_sCardNumber;
    m_sCVC = other.m_sCVC;
    m_sName = other.m_sName;
    m_expirationDate = other.m_expirationDate;
}

//*************************************************************************************************
//*************************************** GETTERS & SETTERS ****************************************
//*************************************************************************************************

string CreditCardPayment::getCardNumber() const
{
    return m_sCardNumber;
}

string CreditCardPayment::getCVC() const
{
    return m_sCVC;
}

string CreditCardPayment::getName() const
{
    return m_sName;
}

Date CreditCardPayment::getExpirationDate() const
{
    return m_expirationDate;
}

void CreditCardPayment::setCardNumber(const string &sCardNumber)
{
    m_sCardNumber = sCardNumber;
}

void CreditCardPayment::setCVC(const string &sCVC)
{
    m_sCVC = sCVC;
}

void CreditCardPayment::setName(const string &sName)
{
    m_sName = sName;
}

void CreditCardPayment::setExpirationDate(const Date &expirationDate)
{
    m_expirationDate = expirationDate;
}

//*************************************************************************************************
//******************************************* METHODS ********************************************
//*************************************************************************************************

void CreditCardPayment::processPayment(double amount) const
{
    std::cout << "Processing credit card payment of " << amount << " VND" << std::endl;
}

//=================================================================================================
//========================================= MOMO PAYMENT ==========================================
//=================================================================================================

//*************************************************************************************************
//******************************** CONSTRUCTORS & DESTRUCTOR **************************************
//*************************************************************************************************

MomoPayment::MomoPayment()
{
    m_sPhoneNumber = "";
}

MomoPayment::MomoPayment(const string &sPhoneNumber)
{
    m_sPhoneNumber = sPhoneNumber;
}

MomoPayment::MomoPayment(const MomoPayment &other)
{
    m_sPhoneNumber = other.m_sPhoneNumber;
}

//*************************************************************************************************
//*************************************** GETTERS & SETTERS ****************************************
//*************************************************************************************************

string MomoPayment::getPhoneNumber() const
{
    return m_sPhoneNumber;
}

void MomoPayment::setPhoneNumber(const string &sPhoneNumber)
{
    m_sPhoneNumber = sPhoneNumber;
}

//*************************************************************************************************
//******************************************* METHODS ********************************************
//*************************************************************************************************

void MomoPayment::processPayment(double amount) const
{
    std::cout << "Processing momo payment of " << amount << " VND" << std::endl;
}
