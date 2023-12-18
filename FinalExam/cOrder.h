/**
 * @file cOrder.h
 * @brief Definition of Order class representing an order and OrderState using State Pattern
 */
#pragma once

#include "cDate.h"
#include <vector>
#include "cProduct.h"
#include "iShippingStrategy.h"

using std::pair;
using std::vector;
// Forward declaration
class Order;

/// @brief State interface of the State Pattern
class OrderState
{
public:
    virtual void processOrder(Order &order) = 0;
    virtual void shipOrder(Order &order) = 0;
    virtual void deliverOrder(Order &order) = 0;
    virtual void cancelOrder(Order &order) = 0;
};

class Order
{
private:
    string m_sOrderCode;                               ///< Order code
    Date m_orderDate;                                  ///< Order date
    OrderState *m_pCurrentOrderState;                  ///< Order state
    unsigned int m_uiQuantity;                         ///< Quantity of the order
    double m_dTotalPrice;                              ///< Total price of the order
    double m_dFinalPrice;                              ///< Final price of the order
    vector<pair<Product *, unsigned int>> m_vProducts; ///< List of products in the order
    ShippingStrategy *m_pShippingStrategy;             ///< Shipping strategy of the order

public: // Constructors & Destructor
    Order();
    Order(const string &sOrderCode, const Date &orderDate, OrderState *pCurrentOrderState, unsigned int uiQuantity, double dTotalPrice, double dFinalPrice, const vector<pair<Product *, unsigned int>> &vProducts, ShippingStrategy *pShippingStrategy);
    Order(const Order &other);
    ~Order();

public: // Getters
    string getOrderCode() const;
    Date getOrderDate() const;
    OrderState *getCurrentOrderState() const;
    unsigned int getQuantity() const;
    double getTotalPrice() const;
    double getFinalPrice() const;
    vector<pair<Product *, unsigned int>> getProducts() const;
    ShippingStrategy *getShippingStrategy() const;

public: // Setters
    void setOrderCode(const string &sOrderCode);
    void setOrderDate(const Date &orderDate);
    void setCurrentOrderState(OrderState *pCurrentOrderState);
    void setQuantity(unsigned int uiQuantity);
    void setTotalPrice(double dTotalPrice);
    void setFinalPrice(double dFinalPrice);
    void setProducts(const vector<pair<Product *, unsigned int>> &vProducts);
    void setShippingStrategy(ShippingStrategy *pShippingStrategy);

public: // Actions
    void process();
    void ship();
    void deliver();
    void cancel();

public: // Methods
    void addProduct(Product *pProduct, unsigned int uiQuantity);
    void removeProduct(Product *pProduct);
};

/// @brief Concrete state class of the State Pattern

/// @brief Concrete state class while the order is in processing state
class ProcessingState : public OrderState
{
public:
    void processOrder(Order &order) override;
    void shipOrder(Order &order) override;
    void deliverOrder(Order &order) override;
    void cancelOrder(Order &order) override;
};

/// @brief Concrete state class while the order is in shipping state
class ShippingState : public OrderState
{
public:
    void processOrder(Order &order) override;
    void shipOrder(Order &order) override;
    void deliverOrder(Order &order) override;
    void cancelOrder(Order &order) override;
};

/// @brief Concrete state class while the order is in delivered state
class DeliveredState : public OrderState
{
public:
    void processOrder(Order &order) override;
    void shipOrder(Order &order) override;
    void deliverOrder(Order &order) override;
    void cancelOrder(Order &order) override;
};

/// @brief Concrete state class while the order is in cancelled state
class CancelledState : public OrderState
{
public:
    void processOrder(Order &order) override;
    void shipOrder(Order &order) override;
    void deliverOrder(Order &order) override;
    void cancelOrder(Order &order) override;
};

/// @brief Enum class representing the state of the order
enum OrderStatus
{
    PROCESSING,
    SHIPPING,
    DELIVERED,
    CANCELLED
};