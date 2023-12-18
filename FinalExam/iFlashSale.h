#pragma once

#include "cProduct.h"

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