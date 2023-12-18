#include "cOrder.h"
#include <iostream>
//======================================================================================================
//============================================= ORDER ==================================================
//======================================================================================================

//******************************************************************************************************
//*********************************** CONSTRUCTORS & DESTRUCTOR ****************************************
//******************************************************************************************************

Order::Order()
{
    m_sOrderCode = "";
    m_orderDate = Date();
    m_pCurrentOrderState = nullptr;
    m_uiQuantity = 0;
    m_dTotalPrice = 0;
    m_dFinalPrice = 0;
    m_vProducts = vector<pair<Product *, unsigned int>>();
    m_pShippingStrategy = nullptr;
}

Order::Order(const string &sOrderCode, const Date &orderDate, OrderState *pCurrentOrderState, unsigned int uiQuantity, double dTotalPrice, double dFinalPrice, const vector<pair<Product *, unsigned int>> &vProducts, ShippingStrategy *pShippingStrategy)
{
    m_sOrderCode = sOrderCode;
    m_orderDate = orderDate;
    m_pCurrentOrderState = pCurrentOrderState;
    m_uiQuantity = uiQuantity;
    m_dTotalPrice = dTotalPrice;
    m_dFinalPrice = dFinalPrice;
    m_vProducts = vProducts;
    m_pShippingStrategy = pShippingStrategy;
}

Order::Order(const Order &other)
{
    m_sOrderCode = other.m_sOrderCode;
    m_orderDate = other.m_orderDate;
    m_pCurrentOrderState = other.m_pCurrentOrderState;
    m_uiQuantity = other.m_uiQuantity;
    m_dTotalPrice = other.m_dTotalPrice;
    m_dFinalPrice = other.m_dFinalPrice;
    m_vProducts = other.m_vProducts;
    m_pShippingStrategy = other.m_pShippingStrategy;
}

Order::~Order()
{
    delete m_pCurrentOrderState;
    m_pCurrentOrderState = nullptr;
}

//******************************************************************************************************
//********************************************* GETTERS ************************************************
//******************************************************************************************************

string Order::getOrderCode() const
{
    return m_sOrderCode;
}

Date Order::getOrderDate() const
{
    return m_orderDate;
}

OrderState *Order::getCurrentOrderState() const
{
    return m_pCurrentOrderState;
}

unsigned int Order::getQuantity() const
{
    return m_uiQuantity;
}

double Order::getTotalPrice() const
{
    return m_dTotalPrice;
}

double Order::getFinalPrice() const
{
    return m_dFinalPrice;
}

vector<pair<Product *, unsigned int>> Order::getProducts() const
{
    return m_vProducts;
}

ShippingStrategy *Order::getShippingStrategy() const
{
    return m_pShippingStrategy;
}

//******************************************************************************************************
//********************************************* SETTERS ************************************************
//******************************************************************************************************

void Order::setOrderCode(const string &sOrderCode)
{
    m_sOrderCode = sOrderCode;
}

void Order::setOrderDate(const Date &orderDate)
{
    m_orderDate = orderDate;
}

void Order::setCurrentOrderState(OrderState *pCurrentOrderState)
{
    delete m_pCurrentOrderState;               // Delete the old state
    m_pCurrentOrderState = pCurrentOrderState; // Set the new state
}

void Order::setQuantity(unsigned int uiQuantity)
{
    m_uiQuantity = uiQuantity;
}

void Order::setTotalPrice(double dTotalPrice)
{
    m_dTotalPrice = dTotalPrice;
}

void Order::setFinalPrice(double dFinalPrice)
{
    m_dFinalPrice = dFinalPrice;
}

void Order::setProducts(const vector<pair<Product *, unsigned int>> &vProducts)
{
    m_vProducts = vProducts;
}

void Order::setShippingStrategy(ShippingStrategy *pShippingStrategy)
{
    m_pShippingStrategy = pShippingStrategy;
}

//******************************************************************************************************
//********************************************* ACTIONS ************************************************
//******************************************************************************************************

void Order::process()
{
    m_pCurrentOrderState->processOrder(*this);
}

void Order::ship()
{
    m_pCurrentOrderState->shipOrder(*this);
}

void Order::deliver()
{
    m_pCurrentOrderState->deliverOrder(*this);
}

void Order::cancel()
{
    m_pCurrentOrderState->cancelOrder(*this);
}

//******************************************************************************************************
//********************************************* METHODS ************************************************
//******************************************************************************************************

void Order::addProduct(Product *pProduct, unsigned int uiQuantity)
{
    // Find if the product already exists
    for (auto it = m_vProducts.begin(); it != m_vProducts.end(); ++it)
    {
        if ((*it).first->getName() == pProduct->getName())
        {
            // If it does, add the quantity of the new product to the existing product
            const unsigned int uiOldQuantity = (*it).second;
            const unsigned int uiNewQuantity = uiQuantity;
            (*it).second = uiOldQuantity + uiNewQuantity;
            return;
        }
    }

    // If it doesn't, add the new product to the list
    m_vProducts.push_back(pair<Product *, unsigned int>(pProduct, uiQuantity));
}

void Order::removeProduct(Product *pProduct)
{
    // Find if the product exists
    for (auto it = m_vProducts.begin(); it != m_vProducts.end(); ++it)
    {
        if ((*it).first->getName() == pProduct->getName())
        {
            // If it does, remove the product from the list
            m_vProducts.erase(it);
            return;
        }
    }
}

//======================================================================================================
//========================================== PROCESSING STATE ==========================================
//======================================================================================================

void ProcessingState::processOrder(Order &order)
{
    std::cout << "Order " << order.getOrderCode() << " is being processed." << std::endl;
    order.setCurrentOrderState(new ShippingState());
}

void ProcessingState::shipOrder(Order &order)
{
    std::cout << "Order " << order.getOrderCode() << " cannot be shipped because it is still being processed." << std::endl;
}

void ProcessingState::deliverOrder(Order &order)
{
    std::cout << "Order " << order.getOrderCode() << " cannot be delivered because it is still being processed." << std::endl;
}

void ProcessingState::cancelOrder(Order &order)
{
    std::cout << "Order " << order.getOrderCode() << " is being canceled." << std::endl;
    order.setCurrentOrderState(new CancelledState());
}

//======================================================================================================
//============================================ SHIPPING STATE ==========================================
//======================================================================================================

void ShippingState::processOrder(Order &order)
{
    std::cout << "Order " << order.getOrderCode() << " cannot be processed because it is already being shipped." << std::endl;
}

void ShippingState::shipOrder(Order &order)
{
    std::cout << "Order " << order.getOrderCode() << " is being shipped." << std::endl;
    order.setCurrentOrderState(new DeliveredState());
}

void ShippingState::deliverOrder(Order &order)
{
    std::cout << "Order " << order.getOrderCode() << " cannot be delivered because it is already being shipped." << std::endl;
}

void ShippingState::cancelOrder(Order &order)
{
    std::cout << "Order " << order.getOrderCode() << " cannot be canceled because it is already being shipped." << std::endl;
}

//======================================================================================================
//=========================================== DELIVERED STATE ==========================================
//======================================================================================================

void DeliveredState::processOrder(Order &order)
{
    std::cout << "Order " << order.getOrderCode() << " cannot be processed because it is already being delivered." << std::endl;
}

void DeliveredState::shipOrder(Order &order)
{
    std::cout << "Order " << order.getOrderCode() << " cannot be shipped because it is already being delivered." << std::endl;
}

void DeliveredState::deliverOrder(Order &order)
{
    std::cout << "Order " << order.getOrderCode() << " is being delivered." << std::endl;
    order.setCurrentOrderState(new DeliveredState());
}

void DeliveredState::cancelOrder(Order &order)
{
    std::cout << "Order " << order.getOrderCode() << " cannot be canceled because it is already being delivered." << std::endl;
}

//======================================================================================================
//=========================================== CANCELLED STATE ==========================================
//======================================================================================================

void CancelledState::processOrder(Order &order)
{
    std::cout << "Order " << order.getOrderCode() << " cannot be processed because it is already being canceled." << std::endl;
}

void CancelledState::shipOrder(Order &order)
{
    std::cout << "Order " << order.getOrderCode() << " cannot be shipped because it is already being canceled." << std::endl;
}

void CancelledState::deliverOrder(Order &order)
{
    std::cout << "Order " << order.getOrderCode() << " cannot be delivered because it is already being canceled." << std::endl;
}

void CancelledState::cancelOrder(Order &order)
{
    std::cout << "Order " << order.getOrderCode() << " is being canceled." << std::endl;
    order.setCurrentOrderState(new CancelledState());
}

//======================================================================================================
//============================================= END ====================================================
//======================================================================================================
