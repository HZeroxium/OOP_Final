#pragma once

#include "iConsoleState.h"
#include "cProduct.h"
#include "cUser.h"
#include "cStore.h"
#include "cShoppingCart.h"
#include "cOrder.h"
#include "iPaymentMethod.h"
#include "iPaymentMethodFactory.h"
#include "iShippingStrategy.h"
#include "iDiscountCode.h"
#include "iProductCategory.h"
#include <memory>

using std::unique_ptr;

/// @brief Console class represents a console
class Console
{
private:
    unique_ptr<ConsoleState> m_pState;     ///< Current state of the console
    User *m_pCurrentUser;                  ///< Current user of the console
    Store *m_pStore;                       ///< Store of the console
    ShoppingCart *m_pShoppingCart;         ///< Shopping cart of the console
    Order *m_pOrder;                       ///< Order of the console
    Product *m_pProduct;                   ///< Product of the console
    ProductCategory *m_pProductCategory;   ///< Product category of the console
    PaymentMethod *m_pPaymentMethod;       ///< Payment method of the console
    DiscountCode *m_pDiscountCode;         ///< Discount code of the console
    ShippingStrategy *m_pShippingStrategy; ///< Shipping strategy of the console

    Console(); ///< Private constructor of the Singleton Pattern

public: // Singleton Methods
    static Console &getInstance();
    Console(const Console &) = delete;
    void operator=(const Console &) = delete;
    ~Console() = default;

public: // Getters
    ConsoleState *getState() const;
    User *getCurrentUser() const;
    Store *getStore() const;
    ShoppingCart *getShoppingCart() const;
    Order *getOrder() const;
    Product *getProduct() const;
    ProductCategory *getProductCategory() const;
    PaymentMethod *getPaymentMethod() const;
    DiscountCode *getDiscountCode() const;
    ShippingStrategy *getShippingStrategy() const;

public: // Setters
    void setState(unique_ptr<ConsoleState> pNewState);
    void setCurrentUser(User *pCurrentUser);
    void setCurrentStore(Store *pStore);
    void setCurrentOrder(Order *pOrder);
    void setCurrentProduct(Product *pProduct);
    void setCurrentProductCategory(ProductCategory *pProductCategory);
    void setCurrentPaymentMethod(PaymentMethod *pPaymentMethod);
    void setCurrentDiscountCode(DiscountCode *pDiscountCode);
    void setCurrentShippingStrategy(ShippingStrategy *pShippingStrategy);

public: // Run
    void run();
};