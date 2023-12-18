#include "iProductIterator.h"

//=====================================================================================================================
//================================ SHOPPING CART ITERATOR ==============================================================
//=====================================================================================================================

ShoppingCartIterator::ShoppingCartIterator(const ShoppingCart *pShoppingCart)
{
    m_pShoppingCart = pShoppingCart;
    m_uiCurrentIndex = 0;
}

void ShoppingCartIterator::first()
{
    m_uiCurrentIndex = 0;
}

void ShoppingCartIterator::next()
{
    m_uiCurrentIndex++;
}

bool ShoppingCartIterator::hasNext()
{
    return m_uiCurrentIndex < m_pShoppingCart->getProductCount();
}

Product *ShoppingCartIterator::currentItem() const
{
    if (hasNext)
        return m_pShoppingCart->getProductAtIndex(m_uiCurrentIndex);
    return nullptr;
}
