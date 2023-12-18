#pragma once

#include <string>
#include <vector>
#include "iFlashSale.h"

using std::string;
using std::vector;

/// @brief Product class represents a product in the store inventory system
class Product : public Observer
{
private:
    string m_sID;              ///< ID of the product
    string m_sName;            ///< Name of the product
    string m_sCategory;        ///< Category of the product
    double m_dPrice;           ///< Price of the product (in VND)
    unsigned int m_uiQuantity; ///< Quantity of the product in stock
    bool m_bIsOnFlashSale;     ///< Whether the product is on sale

public: // Constructors & Destructor
    Product();
    Product(const string &sID, const string &sName, const string &sCategory, double dPrice, unsigned int uiQuantity, bool bIsOnFlashSale = false);
    Product(const Product &other);
    ~Product();

public: // Getters
    string getID() const;
    string getName() const;
    string getCategory() const;
    double getPrice() const;
    unsigned int getQuantity() const;
    bool getFlashSaleStatus() const;

public: // Setters
    void setID(const string &sID);
    void setName(const string &sName);
    void setCategory(const string &sCategory);
    void setPrice(double dPrice);
    void setQuantity(unsigned int uiQuantity);
    void setFlashSale(bool bIsOnFlashSale);

public: // Methods
    void update(bool bFlashSale) override;
};