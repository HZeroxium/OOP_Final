#include "cConsole.h"

//======================================================================================================
//==================================== CONSTRUCTORS & DESTRUCTOR ========================================
//======================================================================================================

Console::Console()
{
    m_pState = std::make_unique<LoginState>();
    m_pCurrentUser = nullptr;
    m_pStore = nullptr;
    m_pShoppingCart = nullptr;
    m_pOrder = nullptr;
    m_pProduct = nullptr;
    m_pProductCategory = nullptr;
    m_pPaymentMethod = nullptr;
    m_pDiscountCode = nullptr;
    m_pShippingStrategy = nullptr;
    m_pDiscountCode = nullptr;
    m_pShippingStrategy = nullptr;
}

//======================================================================================================
//======================================== SINGLETON METHODS ===========================================
//======================================================================================================

Console &Console::getInstance()
{
    static Console instance;
    return instance;
}

//======================================================================================================
//============================================== GETTERS ================================================
//======================================================================================================

ConsoleState *Console::getState() const
{
    return m_pState.get();
}

User *Console::getCurrentUser() const
{
    return m_pCurrentUser;
}

Store *Console::getStore() const
{
    return m_pStore;
}

ShoppingCart *Console::getShoppingCart() const
{
    return m_pShoppingCart;
}

Order *Console::getOrder() const
{
    return m_pOrder;
}

Product *Console::getProduct() const
{
    return m_pProduct;
}

ProductCategory *Console::getProductCategory() const
{
    return m_pProductCategory;
}

PaymentMethod *Console::getPaymentMethod() const
{
    return m_pPaymentMethod;
}

DiscountCode *Console::getDiscountCode() const
{
    return m_pDiscountCode;
}

ShippingStrategy *Console::getShippingStrategy() const
{
    return m_pShippingStrategy;
}

//======================================================================================================
//============================================== SETTERS ================================================
//======================================================================================================

void Console::setState(unique_ptr<ConsoleState> pNewState)
{
    m_pState = std::move(pNewState);
}

void Console::setCurrentUser(User *pCurrentUser)
{
    m_pCurrentUser = pCurrentUser;
}

void Console::setCurrentStore(Store *pStore)
{
    m_pStore = pStore;
}

void Console::setCurrentOrder(Order *pOrder)
{
    m_pOrder = pOrder;
}

void Console::setCurrentProduct(Product *pProduct)
{
    m_pProduct = pProduct;
}

void Console::setCurrentProductCategory(ProductCategory *pProductCategory)
{
    m_pProductCategory = pProductCategory;
}

void Console::setCurrentPaymentMethod(PaymentMethod *pPaymentMethod)
{
    m_pPaymentMethod = pPaymentMethod;
}

void Console::setCurrentDiscountCode(DiscountCode *pDiscountCode)
{
    m_pDiscountCode = pDiscountCode;
}

void Console::setCurrentShippingStrategy(ShippingStrategy *pShippingStrategy)
{
    m_pShippingStrategy = pShippingStrategy;
}

//======================================================================================================
//=============================================== RUN ==================================================
//======================================================================================================

void Console::run()
{
    while (true)
    {
        m_pState->display();
        m_pState->handleInput(*this);
    }
}
