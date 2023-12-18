#include "uDataConverter.h"
#include <sstream>

//******************************************************************************************************
//************************************ SINGLETON METHODS ***********************************************
//******************************************************************************************************

DataConverter &DataConverter::getInstance()
{
    static DataConverter instance;
    return instance;
}

//******************************************************************************************************
//************************************ DATA CONVERSION METHODS *****************************************
//******************************************************************************************************

/// @brief Convert a Product object to a 1 line string with csv format
/// @param product
/// @return
string DataConverter::convertProductToString(const Product &product)
{
    /* Example
    123456,Macbook Pro 2020,Macs,50000000,10,0
    */
    string sProduct = "";
    sProduct += product.getID() + ",";
    sProduct += product.getName() + ",";
    sProduct += product.getCategory() + ",";
    sProduct += std::to_string(product.getPrice()) + ",";
    sProduct += std::to_string(product.getQuantity()) + ",";
    sProduct += std::to_string(product.getFlashSaleStatus()) + ",";
    return sProduct;
}

/// @brief Convert a Customer object to a 1 line string with csv format
/// @param customer
/// @return
string DataConverter::convertCustomerToString(const Customer &customer)
{
    /* Example
    22127154,123456,28/08/2004,Nguyen Gia Huy,huyzerox@gmail.com,0987654321,28/08/2002,Male,Ha Noi,0
    */
    string sCustomer = "";
    sCustomer += customer.getUsername() + ",";
    sCustomer += customer.getPassword() + ",";
    sCustomer += customer.getJoinDate().toString() + ",";
    sCustomer += customer.getFullName() + ",";
    sCustomer += customer.getEmail() + ",";
    sCustomer += customer.getPhoneNumber() + ",";
    sCustomer += customer.getBirthDate().toString() + ",";
    sCustomer += customer.getGender() + ",";
    sCustomer += customer.getAddress() + ",";

    // Convert customer rank to string
    CustomerRank *pCustomerRank = customer.getRank();
    int iCustomerRank = 0;

    if (dynamic_cast<RegularCustomerRank *>(pCustomerRank))
    {
        iCustomerRank = CustomerRankType::REGULAR;
    }
    else if (dynamic_cast<BronzeCustomerRank *>(pCustomerRank))
    {
        iCustomerRank = CustomerRankType::BRONZE;
    }
    else if (dynamic_cast<SilverCustomerRank *>(pCustomerRank))
    {
        iCustomerRank = CustomerRankType::SILVER;
    }
    else if (dynamic_cast<GoldCustomerRank *>(pCustomerRank))
    {
        iCustomerRank = CustomerRankType::GOLD;
    }

    sCustomer += std::to_string(iCustomerRank) + ",";
    return sCustomer;
}

/// @brief Convert a Store object to 1 line string with csv format
/// @param store
/// @return
string DataConverter::convertStoreToString(const Store &store)
{
    /* Example
    Laptop Store,28/08/2020
    */
    const string cDelimiter = ",";
    string sStore = "";
    sStore += store.getName() + cDelimiter;
    sStore += store.getJoinDate().toString() + cDelimiter;
    return sStore;
}

string DataConverter::convertDiscountCodeToString(const DiscountCode *discountCode)
{
    /* Example
    001,overall,10,1000,
    002,category,10,1000,Electronics,
    003,birthday,10,1000,
    */
    string sDiscountCode = "";
    sDiscountCode += discountCode->getCode() + ",";
    if (dynamic_cast<const OverallDiscountCode *>(discountCode))
    {
        sDiscountCode += "overall,";
    }
    else if (dynamic_cast<const CategoryDiscountCode *>(discountCode))
    {
        sDiscountCode += "category,";
    }
    else if (dynamic_cast<const BirthdayDiscountCode *>(discountCode))
    {
        sDiscountCode += "birthday,";
    }

    sDiscountCode += std::to_string(discountCode->getPercentage()) + ",";
    sDiscountCode += std::to_string(discountCode->getMaxAmount()) + ",";

    if (dynamic_cast<const CategoryDiscountCode *>(discountCode))
    {
        sDiscountCode += dynamic_cast<const CategoryDiscountCode *>(discountCode)->getCategory() + ",";
    }
    return sDiscountCode;
}

//******************************************************************************************************
//************************************ STRING TO DATA CONVERSION METHODS *******************************
//******************************************************************************************************

Product DataConverter::convertStringToProduct(const string &sProduct)
{
    constexpr char cDelimiter = ',';
    std::stringstream ss(sProduct);
    string sID, sName, sCategory;
    double dPrice;
    unsigned int uiQuantity;
    bool bFlashSaleStatus;

    std::getline(ss, sID, cDelimiter);
    std::getline(ss, sName, cDelimiter);
    std::getline(ss, sCategory, cDelimiter);
    ss >> dPrice;
    ss.ignore();
    ss >> uiQuantity;
    ss.ignore();
    ss >> bFlashSaleStatus;
    ss.ignore();

    return Product(sID, sName, sCategory, dPrice, uiQuantity, bFlashSaleStatus);
}

Customer DataConverter::convertStringToCustomer(const string &sUser)
{
    constexpr char cDelimiter = ',';
    std::stringstream ss(sUser);
    string sUsername, sPassword, sJoinDate, sFullName, sEmail, sPhoneNumber, sBirthDate, sGender, sAddress, sOrderDirectoryPath, sRankName;

    std::getline(ss, sUsername, cDelimiter);
    std::getline(ss, sPassword, cDelimiter);
    std::getline(ss, sJoinDate, cDelimiter);
    std::getline(ss, sFullName, cDelimiter);
    std::getline(ss, sEmail, cDelimiter);
    std::getline(ss, sPhoneNumber, cDelimiter);
    std::getline(ss, sBirthDate, cDelimiter);
    std::getline(ss, sGender, cDelimiter);
    std::getline(ss, sAddress, cDelimiter);
    std::getline(ss, sRankName, cDelimiter);

    Date joinDate = convertStringToDate(sJoinDate);
    Date birthDate = convertStringToDate(sBirthDate);

    CustomerRank *pRank = nullptr;
    int iRank = std::stoi(sRankName);
    switch (iRank)
    {
    case CustomerRankType::REGULAR:
        pRank = new RegularCustomerRank();
        break;
    case CustomerRankType::BRONZE:
        pRank = new BronzeCustomerRank();
        break;
    case CustomerRankType::SILVER:
        pRank = new SilverCustomerRank();
        break;
    case CustomerRankType::GOLD:
        pRank = new GoldCustomerRank();
        break;
    }

    Customer customer;
    customer.setUsername(sUsername);
    customer.setPassword(sPassword);
    customer.setJoinDate(joinDate);
    customer.setFullName(sFullName);
    customer.setEmail(sEmail);
    customer.setPhoneNumber(sPhoneNumber);
    customer.setBirthDate(birthDate);
    customer.setGender(sGender);
    customer.setAddress(sAddress);
    customer.setRank(pRank);

    return customer; // without orders
};

Date DataConverter::convertStringToDate(const string &sDate)
{
    constexpr char cDelimiter = '/';
    std::stringstream ss(sDate);
    string sDay, sMonth, sYear;

    std::getline(ss, sDay, cDelimiter);
    std::getline(ss, sMonth, cDelimiter);
    std::getline(ss, sYear, cDelimiter);

    unsigned int uiDay = std::stoi(sDay);
    unsigned int uiMonth = std::stoi(sMonth);
    unsigned int uiYear = std::stoi(sYear);

    return Date(uiDay, uiMonth, uiYear);
}

Store DataConverter::convertStringToStore(const string &sStore)
{
    constexpr char cDelimiter = ',';
    std::stringstream ss(sStore);
    string sName, sJoinDate;

    std::getline(ss, sName, cDelimiter);
    std::getline(ss, sJoinDate, cDelimiter);

    Date joinDate = convertStringToDate(sJoinDate);

    return Store(sName, joinDate);
}

DiscountCode *DataConverter::convertStringToDiscountCode(const string &sDiscountCode)
{
    constexpr char cDelimiter = ',';
    std::stringstream ss(sDiscountCode);
    string sType, sCategory, sCode;
    int iPercentage, iMaxAmount;

    std::getline(ss, sCode, cDelimiter);
    std::getline(ss, sType, cDelimiter);
    ss >> iPercentage;
    ss.ignore();
    ss >> iMaxAmount;
    ss.ignore();

    DiscountCode *pDiscountCode = nullptr;
    if (sType == "overall")
    {
        pDiscountCode = new OverallDiscountCode(iPercentage, iMaxAmount);
    }
    else if (sType == "category")
    {
        std::getline(ss, sCategory, cDelimiter);
        pDiscountCode = new CategoryDiscountCode(iPercentage, iMaxAmount, sCategory);
    }
    else if (sType == "birthday")
    {
        pDiscountCode = new BirthdayDiscountCode(iPercentage, iMaxAmount);
    }

    return pDiscountCode;
}