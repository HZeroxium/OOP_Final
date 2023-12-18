#include "iProductBuilder.h"

//======================================================================================================
//====================================== CONCRETE PRODUCT BUILDER ======================================
//======================================================================================================

void ConcreteProductBuilder::buildName(const string &sName)
{
    m_product.setName(sName);
}

void ConcreteProductBuilder::buildCategory(const string &sCategory)
{
    m_product.setCategory(sCategory);
}

void ConcreteProductBuilder::buildPrice(double dPrice)
{
    m_product.setPrice(dPrice);
}

void ConcreteProductBuilder::buildQuantity(unsigned int uiQuantity)
{
    m_product.setQuantity(uiQuantity);
}

Product ConcreteProductBuilder::getProduct()
{
    return m_product;
}

//======================================================================================================
//======================================== PRODUCT DIRECTOR ============================================
//======================================================================================================

ProductDirector::ProductDirector(ProductBuilder *pProductBuilder)
{
    m_pProductBuilder = pProductBuilder;
}

void ProductDirector::makeProduct(const string &sName, const string &sCategory, double dPrice, unsigned int uiQuantity)
{
    m_pProductBuilder->buildName(sName);
    m_pProductBuilder->buildCategory(sCategory);
    m_pProductBuilder->buildPrice(dPrice);
    m_pProductBuilder->buildQuantity(uiQuantity);
}

Product ProductDirector::getProduct()
{
    return m_pProductBuilder->getProduct();
}
