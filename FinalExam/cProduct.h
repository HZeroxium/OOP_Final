#pragma once

#include <vector>
#include <string>
#include "cReview.h"
using std::string;
using std::vector;

/// @brief Observer interface using the Observer design pattern
class Observer
{
public:
    virtual void update(bool bFlashSale) = 0;
    virtual ~Observer() = default;
};

/// @brief Subject interface using the Observer design pattern
class Subject
{
public:
    virtual void addObserver(Observer *) = 0;
    virtual void removeObserver(Observer *) = 0;
    virtual void notifyObservers() = 0;
    virtual ~Subject() = default;
};

/// @brief Concrete implementation of Product class
class Product : public Observer
{
private:
    string m_sID;              ///< ID of the product
    string m_sName;            ///< Name of the product
    string m_sCategory;        ///< Category of the product
    double m_dPrice;           ///< Price of the product (in VND)
    unsigned int m_uiQuantity; ///< Quantity of the product in stock
    bool m_bIsOnFlashSale;     ///< Whether the product is on sale
    vector<Review> m_vReviews; ///< List of reviews

public: // Constructors & Destructor
    Product();
    Product(const string &sID, const string &sName, const string &sCategory, double dPrice, unsigned int uiQuantity, bool bIsOnFlashSale = false);
    Product(const Product &other);
    ~Product() override;

public: // Getters
    string getID() const;
    string getName() const;
    string getCategory() const;
    double getPrice() const;
    unsigned int getQuantity() const;
    bool getFlashSaleStatus() const;
    vector<Review> getReviews() const;

public: // Setters
    void setID(const string &sID);
    void setName(const string &sName);
    void setCategory(const string &sCategory);
    void setPrice(double dPrice);
    void setQuantity(unsigned int uiQuantity);
    void setFlashSale(bool bIsOnFlashSale);
    void setReviews(const vector<Review> &vReviews);

public: // Methods
    void update(bool bFlashSale) override;
    void addReview(const Review &review);
};

/// @brief Concrete implementation of FlashSale class
class FlashSale : public Subject
{
private:
    bool m_bIsOnFlashSale;           ///< Whether the product is on sale
    vector<Observer *> m_vObservers; ///< List of observers

public: // Constructors & Destructor
    FlashSale();

public: // Observer methods
    void addObserver(Observer *) override;
    void removeObserver(Observer *) override;
    void notifyObservers() override;

public: // FlashSale methods
    void setFlashSaleStatus(Product *product, bool bIsOnFlashSale);
    void setFlashSaleStatus(bool bIsOnFlashSale);
    constexpr static double FLASH_SALE_PERCENTAGE = 0.2; ///< Percentage of discount for flash sale
};