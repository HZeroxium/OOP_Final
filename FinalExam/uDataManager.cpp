#include "uDataManager.h"
#include "uDataStorage.h"
#include <fstream>
#include <iostream>

//******************************************************************************************************
//************************************ SINGLETON METHODS ***********************************************
//******************************************************************************************************

DataManager &DataManager::getInstance()
{
    static DataManager instance;
    return instance;
}

DataManager::~DataManager()
{
    for (const User *pUser : m_vUsers)
    {
        delete pUser;
    }
    for (const DiscountCode *pDiscountCode : m_vDiscountCodes)
    {
        delete pDiscountCode;
    }

    m_vUsers.clear();
    m_vDiscountCodes.clear();
    std::cout << "DataManager destructor called" << std::endl;
}

//******************************************************************************************************
//************************************** GETTERS ********************************************************
//******************************************************************************************************

//******************************************************************************************************
//*********************************** SAVE DATA HELPER METHODS ******************************************
//******************************************************************************************************

/// @brief Save product list to file with csv format
bool DataManager::saveProducts() const
{
    const string sProductFilePath = DataStorageSystem::getInstance().getProductListFilePath();
    std::ofstream fout(sProductFilePath);

    if (!fout.is_open())
    {
        std::cout << "!!!ERROR: Cannot open file " << sProductFilePath << " to save data" << std::endl;
        return false;
    }
    // Write header
    fout << "ProductID,ProductName,Category,Price,Quantity,FlashSale," << std::endl;

    for (const Product &product : m_vProducts)
    {
        const string sProduct = DataConverter::getInstance().convertProductToString(product);
        fout << sProduct << std::endl;
    }

    fout.close();
    return true;
}

/// @brief Save user list to file with csv format
bool DataManager::saveUsers() const
{
    const string sUserFilePath = DataStorageSystem::getInstance().getUserListFilePath();
    std::ofstream fout(sUserFilePath);

    if (!fout.is_open())
    {
        std::cout << "!!!ERROR: Cannot open file " << sUserFilePath << " to save data" << std::endl;
        return false;
    }

    // Write header
    fout << "Username,Password,Join date,Fullname,Email,Phone number,Birthday,Gender,Address,Rank," << std::endl;

    for (const User *pUser : m_vUsers)
    {
        // Check if user is a customer
        if (const auto *pCustomer = dynamic_cast<const Customer *>(pUser))
        {
            const string sCustomer = DataConverter::getInstance().convertCustomerToString(*pCustomer);
            fout << sCustomer << std::endl;
            saveOrders(*pCustomer);
        }
    }

    fout.close();
    return true;
}

/// @brief Save order list to file with csv format
bool DataManager::saveOrders(const Customer &customer)
{
    const string sOrderDirectoryPath = DataStorageSystem::getInstance().getCustomerOrderDirectoryPath(customer);

    const vector<Order> &vOrders = customer.getOrders();

    for (const Order &order : vOrders)
    {
        const string sOrderFilePath = DataStorageSystem::getInstance().getCustomerOrderFilePath(customer, order);
        std::ofstream fout(sOrderFilePath);

        if (!fout.is_open())
        {
            std::cout << "!!!ERROR: Cannot open file " << sOrderFilePath << " to save data" << std::endl;
            return false;
        }

        const string sOrderCode = order.getOrderCode();
        const string sOrderDate = order.getOrderDate().toString();

        // Convert order state to string
        OrderState *pOrderState = order.getCurrentOrderState();
        int iOrderState = 0;
        if (dynamic_cast<ProcessingState *>(pOrderState))
        {
            iOrderState = OrderStatus::PROCESSING;
        }
        else if (dynamic_cast<ShippingState *>(pOrderState))
        {
            iOrderState = OrderStatus::SHIPPING;
        }
        else if (dynamic_cast<DeliveredState *>(pOrderState))
        {
            iOrderState = OrderStatus::DELIVERED;
        }
        else if (dynamic_cast<CancelledState *>(pOrderState))
        {
            iOrderState = OrderStatus::CANCELLED;
        }

        const string sOrderState = std::to_string(iOrderState);
        const string sQuantity = std::to_string(order.getQuantity());
        const string sTotalPrice = std::to_string(order.getTotalPrice());
        const string sFinalPrice = std::to_string(order.getFinalPrice());

        fout << sOrderCode << std::endl;
        fout << sOrderDate << std::endl;
        fout << sOrderState << std::endl;
        fout << sQuantity << std::endl;
        fout << sTotalPrice << std::endl;
        fout << sFinalPrice << std::endl;

        const vector<pair<Product *, unsigned int>> &vProducts = order.getProducts();

        fout << vProducts.size() << std::endl;

        for (const auto &[pProduct, uiQuantity] : vProducts)
        {
            const string sProductID = pProduct->getID();
            const string sQuantity = std::to_string(uiQuantity);

            fout << sProductID << ",";
            fout << sQuantity << std::endl;
        }

        // Convert shipping strategy to string
        ShippingStrategy *pShippingStrategy = order.getShippingStrategy();
        int iShippingStrategy = 0;
        if (dynamic_cast<StandardShipping *>(pShippingStrategy))
        {
            iShippingStrategy = ShippingStrategyType::STANDARD;
        }
        else if (dynamic_cast<ExpressShipping *>(pShippingStrategy))
        {
            iShippingStrategy = ShippingStrategyType::EXPRESS;
        }

        const string sShippingStrategy = std::to_string(iShippingStrategy);

        fout << sShippingStrategy << std::endl;
        fout.close();
    }
    return true;
};

/// @brief Save store list to file with csv format
bool DataManager::saveStores() const
{
    const string sStoreFilePath = DataStorageSystem::getInstance().getStoreListFilePath();
    std::ofstream fout(sStoreFilePath);

    if (!fout.is_open())
    {
        std::cout << "!!!ERROR: Cannot open file " << sStoreFilePath << " to save data" << std::endl;
        return false;
    }

    // Write header
    fout << "StoreName,JoinDate," << std::endl;

    for (const Store &store : m_vStores)
    {
        const string sStore = DataConverter::getInstance().convertStoreToString(store);
        fout << sStore << std::endl;
        saveStoreProductList(store);
    }

    fout.close();
    return true;
}

/// @brief Save store product list to file with csv format
bool DataManager::saveStoreProductList(const Store &store)
{
    const string sStoreProductListFilePath = DataStorageSystem::getInstance().getSpecificProductListFilePath(store);
    std::ofstream fout(sStoreProductListFilePath);

    if (!fout.is_open())
    {
        std::cout << "!!!ERROR: Cannot open file " << sStoreProductListFilePath << " to save data" << std::endl;
        return false;
    }
    // Remove const-quanlifier to call getProducts()
    auto &storeRef = const_cast<Store &>(store);

    const vector<Product *> &vProducts = storeRef.getProducts();

    for (const Product *product : vProducts)
    {
        const string sProduct = DataConverter::getInstance().convertProductToString(*product);
        fout << sProduct << std::endl;
    }

    fout.close();
    return true;
}

/// @brief Save product category list to file with tree-like structure using "-" to indicate level
void DataManager::saveProductCategories(const ProductCategory &productCategory, std::ofstream &fout)
{
    /* Example
    Electronics
    -Laptop
    --Asus
    --Dell
    --HP
    -Phone
    --Apple
    --Samsung
    Shoes
    -Nike
    -Adidas
    --Adidas Superstar
    --Adidas Stan Smith
    */

    // const string sCategoryName = productCategory.getName();
    // static int iLevel = 0;
    // string sLevel = "";
    // for (int i = 0; i < iLevel; ++i)
    //{
    //     sLevel += "-";
    // }

    // fout << sLevel << sCategoryName << std::endl;

    //// Remove const-quanlifier to call getSubCategories()
    // ProductCategory &productCategoryRef = const_cast<ProductCategory &>(productCategory);
    //// Check if product category has sub-categories
    // if (const CompositeProductCategory *pCompositeProductCategory = dynamic_cast<CompositeProductCategory *>(&productCategoryRef))
    //{
    //     ++iLevel;
    //     const vector<ProductCategory *> &vSubCategories = pCompositeProductCategory->getSubCategories();
    //     for (const ProductCategory *pSubCategory : vSubCategories)
    //     {
    //         saveProductCategories(*pSubCategory, fout);
    //     }
    //     --iLevel;
    // }
    // else
    //{
    //     return;
    // }
    return;
}

/// @brief Save product category list to file with tree-like structure
bool DataManager::saveProductCategories() const
{
    const string sProductCategoryFilePath = DataStorageSystem::getInstance().getCategoryListFilePath();
    std::ofstream fout(sProductCategoryFilePath);

    if (!fout.is_open())
    {
        std::cout << "!!!ERROR: Cannot open file " << sProductCategoryFilePath << " to save data" << std::endl;
        return false;
    }

    for (const ProductCategory &productCategory : m_vProductCategories)
    {
        saveProductCategories(productCategory, fout);
    }

    fout.close();
    return true;
}

/// @brief Save discount code list to file with csv format
bool DataManager::saveDiscountCodes() const
{
    const string sDiscountCodeFilePath = DataStorageSystem::getInstance().getDiscountCodeListFilePath();
    std::ofstream fout(sDiscountCodeFilePath);

    if (!fout.is_open())
    {
        std::cout << "!!!ERROR: Cannot open file " << sDiscountCodeFilePath << " to save data" << std::endl;
        return false;
    }

    // Write header
    fout << "Code, Type, Percentage, MaxAmount, Category," << std::endl;

    for (const DiscountCode *pDiscountCode : m_vDiscountCodes)
    {
        const string sDiscountCode = DataConverter::getInstance().convertDiscountCodeToString(pDiscountCode);
        fout << sDiscountCode << std::endl;
    }

    fout.close();
    return true;
}

/// @brief Save review list to file with csv format
bool DataManager::saveReviews(const Product &product)
{
    const string sReviewFilePath = DataStorageSystem::getInstance().getProductReviewFilePath(product);
    std::ofstream fout(sReviewFilePath);

    if (!fout.is_open())
    {
        std::cout << "!!!ERROR: Cannot open file " << sReviewFilePath << " to save data" << std::endl;
        return false;
    }

    const vector<Review> &vReviews = product.getReviews();

    for (const Review &review : vReviews)
    {
        const string sReview = DataConverter::getInstance().convertReviewToString(review);
        fout << sReview << std::endl;
    }

    fout.close();

    return true;
};
//******************************************************************************************************
//******************************** LOAD DATA HELPER METHODS ********************************************
//******************************************************************************************************

/// @brief Load product list from file with csv format
bool DataManager::loadProducts()
{
    const string sProductFilePath = DataStorageSystem::getInstance().getProductListFilePath();
    std::ifstream fin(sProductFilePath);

    if (!fin.is_open())
    {
        std::cout << "!!!ERROR: Cannot open file " << sProductFilePath << " to load data" << std::endl;
        return false;
    }

    string sProduct;

    // Skip header
    std::getline(fin, sProduct);
    while (std::getline(fin, sProduct))
    {
        Product product = DataConverter::getInstance().convertStringToProduct(sProduct);
        loadReviews(product);
        m_vProducts.push_back(product);
    }

    fin.close();
    return true;
}

/// @brief Load user list from file with csv format
bool DataManager::loadUsers()
{
    const string sUserFilePath = DataStorageSystem::getInstance().getUserListFilePath();
    std::ifstream fin(sUserFilePath);

    if (!fin.is_open())
    {
        std::cout << "!!!ERROR: Cannot open file " << sUserFilePath << " to load data" << std::endl;
        return false;
    }

    string sUser;
    // Skip header
    std::getline(fin, sUser);

    while (std::getline(fin, sUser))
    {
        Customer customer = DataConverter::getInstance().convertStringToCustomer(sUser);
        customer.loadAdditionalData();
        User *pUser = new Customer(customer);
        m_vUsers.push_back(pUser);
    }

    fin.close();
    return true;
}

/// @brief Load order list from file with csv format
bool DataManager::loadOrders(const Customer &customer)
{
    const string sOrderDirectoryPath = DataStorageSystem::getInstance().getCustomerOrderDirectoryPath(customer);

    const vector<Order> &vOrders = customer.getOrders();

    for (const Order &order : vOrders)
    {
        const string sOrderFilePath = DataStorageSystem::getInstance().getCustomerOrderFilePath(customer, order);
        std::ifstream fin(sOrderFilePath);

        if (!fin.is_open())
        {
            std::cout << "!!!ERROR: Cannot open file " << sOrderFilePath << " to load data" << std::endl;
            return false;
        }

        string sOrderCode, sOrderDate, sOrderState, sQuantity, sTotalPrice, sFinalPrice;
        std::getline(fin, sOrderCode);
        std::getline(fin, sOrderDate);
        std::getline(fin, sOrderState);
        std::getline(fin, sQuantity);
        std::getline(fin, sTotalPrice);
        std::getline(fin, sFinalPrice);

        const Date orderDate = DataConverter::getInstance().convertStringToDate(sOrderDate);
        const unsigned int uiQuantity = std::stoi(sQuantity);
        const double dTotalPrice = std::stod(sTotalPrice);
        const double dFinalPrice = std::stod(sFinalPrice);

        // Convert order state to enum
        OrderState *pOrderState = nullptr;
        switch (int iOrderState = std::stoi(sOrderState))
        {
        case OrderStatus::PROCESSING:
            pOrderState = new ProcessingState();
            break;
        case OrderStatus::SHIPPING:
            pOrderState = new ShippingState();
            break;
        case OrderStatus::DELIVERED:
            pOrderState = new DeliveredState();
            break;
        case OrderStatus::CANCELLED:
            pOrderState = new CancelledState();
            break;
        default:
            break;
        }

        Order newOrder;
        newOrder.setOrderCode(sOrderCode);
        newOrder.setOrderDate(orderDate);
        newOrder.setCurrentOrderState(pOrderState);
        newOrder.setQuantity(uiQuantity);
        newOrder.setTotalPrice(dTotalPrice);
        newOrder.setFinalPrice(dFinalPrice);

        string sProductQuantity;
        std::getline(fin, sProductQuantity);
        const unsigned int uiProductQuantity = std::stoi(sProductQuantity);

        for (unsigned int i = 0; i < uiProductQuantity; ++i)
        {
            string sProductID, sQuantity;
            std::getline(fin, sProductID, ',');
            std::getline(fin, sQuantity);
            // Find product by ID
            for (Product &product : m_vProducts)
            {
                if (product.getID() == sProductID)
                {
                    newOrder.addProduct(&product, std::stoi(sQuantity));
                    break;
                }
            }
        }
    }
    return true;
};

/// @brief Load store list from file with csv format
bool DataManager::loadStores()
{
    const string sStoreFilePath = DataStorageSystem::getInstance().getStoreListFilePath();
    std::ifstream fin(sStoreFilePath);

    if (!fin.is_open())
    {
        std::cout << "!!!ERROR: Cannot open file " << sStoreFilePath << " to load data" << std::endl;
        return false;
    }

    string sStore;
    // Skip header
    std::getline(fin, sStore);
    while (std::getline(fin, sStore))
    {
        Store store = DataConverter::getInstance().convertStringToStore(sStore);
        m_vStores.push_back(store);
        loadStoreProductList(store);
    }

    fin.close();
    return true;
}

/// @brief Load store product list from file with csv format
bool DataManager::loadStoreProductList(Store &store)
{
    const string sStoreProductListFilePath = DataStorageSystem::getInstance().getSpecificProductListFilePath(store);
    std::ifstream fin(sStoreProductListFilePath);

    if (!fin.is_open())
    {
        std::cout << "!!!ERROR: Cannot open file " << sStoreProductListFilePath << " to load data" << std::endl;
        return false;
    }

    string sProduct;
    while (std::getline(fin, sProduct))
    {
        Product product = DataConverter::getInstance().convertStringToProduct(sProduct);
        store.addProduct(&product);
    }

    fin.close();
    return true;
}

/// @brief Load product category list from file with tree-like structure
void DataManager::loadProductCategories(ProductCategory &productCategory, std::ifstream &fin)
{
    /* Example
    Electronics
    -Laptop
    --Asus
    --Dell
    --HP
    -Phone
    --Apple
    --Samsung
    Shoes
    -Nike
    -Adidas
    --Adidas Superstar
    --Adidas Stan Smith
    */

    // string sCategoryName;
    // std::getline(fin, sCategoryName);

    //// Remove const-quanlifier to call addSubCategory()
    // ProductCategory &productCategoryRef = const_cast<ProductCategory &>(productCategory);
    // productCategoryRef.setName(sCategoryName);

    // string sSubCategory;
    // while (std::getline(fin, sSubCategory))
    //{
    //     if (sSubCategory[0] == '-')
    //     {
    //         // Remove "-" from string
    //         sSubCategory.erase(0, 1);
    //         // Add sub-category
    //         CompositeProductCategory *pCompositeProductCategory = dynamic_cast<CompositeProductCategory *>(&productCategoryRef);
    //         if (pCompositeProductCategory)
    //         {
    //             ProductCategory *pProductCategory = new LeafProductCategory(sSubCategory);
    //             pCompositeProductCategory->addSubCategory(pProductCategory);
    //         }
    //     }
    //     else
    //     {
    //         // Go back to previous line
    //         fin.seekg(-sSubCategory.length(), std::ios::cur);
    //         break;
    //     }
    // }

    //// Check if product category has sub-categories
    // const CompositeProductCategory *pCompositeProductCategory = dynamic_cast<CompositeProductCategory *>(&productCategoryRef);
    // if (pCompositeProductCategory)
    //{
    //     const vector<ProductCategory *> &vSubCategories = pCompositeProductCategory->getSubCategories();
    //     for (ProductCategory *pSubCategory : vSubCategories)
    //     {
    //         loadProductCategories(*pSubCategory, fin);
    //     }
    // }
}

/// @brief Load product category list from file with tree-like structure
bool DataManager::loadProductCategories()
{
    return true;
}

/// @brief Load discount code list from file with csv format
bool DataManager::loadDiscountCodes()
{
    const string sDiscountCodeFilePath = DataStorageSystem::getInstance().getDiscountCodeListFilePath();
    std::ifstream fin(sDiscountCodeFilePath);

    if (!fin.is_open())
    {
        std::cout << "!!!ERROR: Cannot open file " << sDiscountCodeFilePath << " to load data" << std::endl;
        return false;
    }

    string sDiscountCode;
    // Skip header
    std::getline(fin, sDiscountCode);
    while (std::getline(fin, sDiscountCode))
    {
        DiscountCode *pDiscountCode = DataConverter::getInstance().convertStringToDiscountCode(sDiscountCode);
        m_vDiscountCodes.push_back(pDiscountCode);
    }

    fin.close();
    return true;
}

/// @brief Load review list from file with csv format
bool DataManager::loadReviews(Product &product)
{
    const string sReviewFilePath = DataStorageSystem::getInstance().getProductReviewFilePath(product);
    std::ifstream fin(sReviewFilePath);

    if (!fin.is_open())
    {
        std::cout << "!!!ERROR: Cannot open file " << sReviewFilePath << " to load data" << std::endl;
        return false;
    }

    string sReview;
    while (std::getline(fin, sReview))
    {
        Review review = DataConverter::getInstance().convertStringToReview(sReview);
        product.addReview(review);
    }

    fin.close();
    return true;
}
//******************************************************************************************************
//************************************** GETTERS *******************************************************
//******************************************************************************************************

vector<Product> &DataManager::getProducts()
{
    return m_vProducts;
}

vector<User *> &DataManager::getUsers()
{
    return m_vUsers;
}

vector<Order> &DataManager::getOrders()
{
    return m_vOrders;
}

vector<Store> &DataManager::getStores()
{
    return m_vStores;
}

vector<ProductCategory> &DataManager::getProductCategories()
{
    return m_vProductCategories;
}

vector<DiscountCode *> &DataManager::getDiscountCodes()
{
    return m_vDiscountCodes;
}

//******************************************************************************************************
//************************************** ACCESSORS *****************************************************
//******************************************************************************************************

Product *DataManager::getProduct(const string &sProductName) const
{
    for (const Product &product : m_vProducts)
    {
        if (product.getName() == sProductName)
        {
            // Remove const-quanlifier to return a non-const pointer

            Product &productRef = const_cast<Product &>(product);
            Product *pProduct = &productRef;
            return pProduct;
        }
    }
    return nullptr;
}

Product *DataManager::getProductByCategory(const string &sProductName, const string &sProductCategoryName) const
{
    for (const Product &product : m_vProducts)
    {
        if (product.getName() == sProductName && product.getCategory() == sProductCategoryName)
        {
            // Remove const-quanlifier to return a non-const pointer

            Product &productRef = const_cast<Product &>(product);
            Product *pProduct = &productRef;
            return pProduct;
        }
    }
    return nullptr;
}

User *DataManager::getUser(const string &sUsername, const string &password) const
{
    for (User *pUser : m_vUsers)
    {
        if (pUser->getUsername() == sUsername && pUser->getPassword() == password)
        {
            return pUser;
        }
    }
    return nullptr;
}

Store *DataManager::getStore(const string &sStoreName) const
{
    for (const Store &store : m_vStores)
    {
        if (store.getName() == sStoreName)
        {
            // Remove const-quanlifier to return a non-const pointer

            Store &storeRef = const_cast<Store &>(store);
            Store *pStore = &storeRef;
            return pStore;
        }
    }
    return nullptr;
}

ProductCategory *DataManager::getProductCategory(const string &sProductCategoryName) const
{
    for (const ProductCategory &productCategory : m_vProductCategories)
    {
        if (productCategory.getName() == sProductCategoryName)
        {
            // Remove const-quanlifier to return a non-const pointer

            ProductCategory &productCategoryRef = const_cast<ProductCategory &>(productCategory);
            ProductCategory *pProductCategory = &productCategoryRef;
            return pProductCategory;
        }
    }
    return nullptr;
}

DiscountCode *DataManager::getDiscountCode(const string &sDiscountCodeName) const
{
    for (DiscountCode *pDiscountCode : m_vDiscountCodes)
    {
        if (pDiscountCode->getCode() == sDiscountCodeName)
        {
            return pDiscountCode;
        }
    }
    return nullptr;
}

//******************************************************************************************************
//************************************** DATA MANAGEMENT METHODS ***************************************
//******************************************************************************************************

bool DataManager::loadData()
{
    return loadProducts() && loadUsers() && loadStores() && loadProductCategories() && loadDiscountCodes();
}

bool DataManager::saveData() const
{
    return saveProducts() && saveUsers() && saveStores() && saveProductCategories() && saveDiscountCodes();
}
