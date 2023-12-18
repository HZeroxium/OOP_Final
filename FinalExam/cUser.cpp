#include "cUser.h"

//======================================================================================================
//==================================== USER ============================================================
//======================================================================================================

//******************************************************************************************************
//************************************ CONSTRUCTORS & DESTRUCTOR ****************************************
//******************************************************************************************************

User::User()
{
    m_sUsername = "";
    m_sPassword = "";
    m_joinDate = Date();
    m_sFullName = "";
    m_sEmail = "";
    m_sPhoneNumber = "";
    m_birthDate = Date();
    m_sGender = "";
}

User::User(const string &sUsername, const string &sPassword)
{
    m_sUsername = sUsername;
    m_sPassword = sPassword;
    m_joinDate = Date();
    m_sFullName = "";
    m_sEmail = "";
    m_sPhoneNumber = "";
    m_birthDate = Date();
    m_sGender = "";
}

User::User(const string &sUsername, const string &sPassword, const Date &joinDate, const string &sFullName, const string &sEmail, const string &sPhoneNumber, const Date &birthDate, const string &sGender)
{
    m_sUsername = sUsername;
    m_sPassword = sPassword;
    m_joinDate = joinDate;
    m_sFullName = sFullName;
    m_sEmail = sEmail;
    m_sPhoneNumber = sPhoneNumber;
    m_birthDate = birthDate;
    m_sGender = sGender;
}

User::User(const User &other)
{
    m_sUsername = other.m_sUsername;
    m_sPassword = other.m_sPassword;
    m_joinDate = other.m_joinDate;
    m_sFullName = other.m_sFullName;
    m_sEmail = other.m_sEmail;
    m_sPhoneNumber = other.m_sPhoneNumber;
    m_birthDate = other.m_birthDate;
    m_sGender = other.m_sGender;
}

//******************************************************************************************************
//********************************************** GETTERS ***********************************************
//******************************************************************************************************

string User::getUsername() const
{
    return m_sUsername;
}

string User::getPassword() const
{
    return m_sPassword;
}

Date User::getJoinDate() const
{
    return m_joinDate;
}

string User::getFullName() const
{
    return m_sFullName;
}

string User::getEmail() const
{
    return m_sEmail;
}

string User::getPhoneNumber() const
{
    return m_sPhoneNumber;
}

Date User::getBirthDate() const
{
    return m_birthDate;
}

string User::getGender() const
{
    return m_sGender;
}

//******************************************************************************************************
//********************************************** SETTERS ***********************************************
//******************************************************************************************************

void User::setUsername(const string &sUsername)
{
    m_sUsername = sUsername;
}

void User::setPassword(const string &sPassword)
{
    m_sPassword = sPassword;
}

void User::setJoinDate(const Date &joinDate)
{
    m_joinDate = joinDate;
}

void User::setFullName(const string &sFullName)
{
    m_sFullName = sFullName;
}

void User::setEmail(const string &sEmail)
{
    m_sEmail = sEmail;
}

void User::setPhoneNumber(const string &sPhoneNumber)
{
    m_sPhoneNumber = sPhoneNumber;
}

void User::setBirthDate(const Date &birthDate)
{
    m_birthDate = birthDate;
}

void User::setGender(const string &sGender)
{
    m_sGender = sGender;
}

//******************************************************************************************************
//********************************************** METHODS ***********************************************
//******************************************************************************************************

//======================================================================================================
//==================================== CUSTOMER ========================================================
//======================================================================================================

//******************************************************************************************************
//************************************ CONSTRUCTORS & DESTRUCTOR ****************************************
//******************************************************************************************************

Customer::Customer()
{
    m_sAddress = "";
    m_vOrders.clear();
    m_pRank = new RegularCustomerRank();
}

Customer::Customer(const string &sUsername, const string &sPassword)
{
    m_sUsername = sUsername;
    m_sPassword = sPassword;
    m_joinDate = Date();
    m_sFullName = "";
    m_sEmail = "";
    m_sPhoneNumber = "";
    m_birthDate = Date();
    m_sGender = "";
    m_sAddress = "";
    m_vOrders.clear();
    m_pRank = new RegularCustomerRank();
}

Customer::Customer(const string &sUsername, const string &sPassword, const Date &joinDate, const string &sFullName, const string &sEmail, const string &sPhoneNumber, const Date &birthDate, const string &sGender, const string &sAddress, const vector<Order> &vOrders, CustomerRank *pRank)
{
    m_sUsername = sUsername;
    m_sPassword = sPassword;
    m_joinDate = joinDate;
    m_sFullName = sFullName;
    m_sEmail = sEmail;
    m_sPhoneNumber = sPhoneNumber;
    m_birthDate = birthDate;
    m_sGender = sGender;
    m_sAddress = sAddress;
    m_vOrders = vOrders;
    m_pRank = pRank;
}

Customer::Customer(const Customer &other)
{
    m_sUsername = other.m_sUsername;
    m_sPassword = other.m_sPassword;
    m_joinDate = other.m_joinDate;
    m_sFullName = other.m_sFullName;
    m_sEmail = other.m_sEmail;
    m_sPhoneNumber = other.m_sPhoneNumber;
    m_birthDate = other.m_birthDate;
    m_sGender = other.m_sGender;
    m_sAddress = other.m_sAddress;
    m_vOrders = other.m_vOrders;

    m_pRank = new RegularCustomerRank();
}

//******************************************************************************************************
//********************************************** GETTERS ***********************************************
//******************************************************************************************************

string Customer::getAddress() const
{
    return m_sAddress;
}

vector<Order> Customer::getOrders() const
{
    return m_vOrders;
}

CustomerRank *Customer::getRank() const
{
    return m_pRank;
}

//******************************************************************************************************
//********************************************** SETTERS ***********************************************
//******************************************************************************************************

void Customer::setAddress(const string &sAddress)
{
    m_sAddress = sAddress;
}

void Customer::setOrders(const vector<Order> &vOrders)
{
    m_vOrders = vOrders;
}

void Customer::setRank(CustomerRank *pRank)
{
    m_pRank = pRank;
}

//******************************************************************************************************
//********************************************** METHODS ***********************************************
//******************************************************************************************************

void Customer::loadOrders()
{
    m_vOrders.clear();

    // Load orders
}

//******************************************************************************************************
//********************************************** METHODS ***********************************************
//******************************************************************************************************

void Customer::addOrder(const Order &order)
{
    // Check if the order is already in the list by comparing the order ID
    for (auto &o : m_vOrders)
    {
        if (o.getOrderCode() == order.getOrderCode())
        {
            return;
        }
    }

    // Add the order to the list
    m_vOrders.push_back(order);
}

void Customer::display() const
{
    // Display customer info
}

void Customer::loadAdditionalData()
{
    loadOrders();
}