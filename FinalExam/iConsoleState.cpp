#include "iConsoleState.h"

#include "uConsoleDecorator.h"
#include "uDataManager.h"
#include "cShoppingCart.h"

using std::cin;

//=================================================================================================
//============================================= LOGIN STATE =======================================
//=================================================================================================

void LoginState::display()
{
    console::printPrimaryHeader("Login");
    console::printOption({"1. Login", "2. Register", "0. Exit"});
}

void LoginState::handleInput(Console &console)
{
    int iChoice;
    cout << "Enter your choice: ";
    cin >> iChoice;
    cin.ignore();

    if (iChoice < 0 || iChoice > 2)
    {
        console::printError("Invalid choice!");
        return;
    }

    if (iChoice == 0)
    {
        console.setState(std::make_unique<ExitState>());
        return;
    }

    // Login session
    if (iChoice == 1)
    {
        string sUsername, sPassword;
        cout << "Enter your username: ";
        getline(cin, sUsername);
        cout << "Enter your password: ";
        getline(cin, sPassword);
        User *pUser = DataManager::getInstance().getUser(sUsername, sPassword);
        if (pUser == nullptr)
        {
            console::printError("Invalid username or password!");
            return;
        }
        else
        {
            console.setCurrentUser(pUser);
            console.setState(std::make_unique<HomeState>());
        }
    }

    // Register session
    if (iChoice == 2)
    {
        string sUsername, sPassword, sName, sAddress, sPhone;
        cout << "Enter your username: ";
        getline(cin, sUsername);
        cout << "Enter your password: ";
        getline(cin, sPassword);
        User *pUser = DataManager::getInstance().getUser(sUsername, sPassword);
        if (pUser != nullptr)
        {
            console::printError("Username already exists!");
            return;
        }
        else
        {
            DataManager::getInstance().getUsers().push_back(new Customer(sUsername, sPassword));
            console.setCurrentUser(pUser);
            console::printSuccess("Register successfully!");
            // Back to login screen
            console.setState(std::make_unique<LoginState>());
        }
    }
}

//==================================================================================================
//============================================= HOME STATE =========================================
//==================================================================================================

void HomeState::display()
{
    console::printPrimaryHeader("Home Page");
    vector<string> vOptions = {"1. Find a product", "2. Find a store", "3. View product by category", "4. View shopping cart", "5. View customer information", "0. Logout"};
    console::printOption(vOptions);
}

void HomeState::handleInput(Console &console)
{
    int iChoice;
    cout << "Enter your choice: ";
    cin >> iChoice;
    cin.ignore();

    if (iChoice < 0 || iChoice > 5)
    {
        console::printError("Invalid choice!");
        return;
    }

    if (iChoice == 0)
    {
        console.setCurrentUser(nullptr);
        console::printNotification("Logout successfully!");
        console.setState(std::make_unique<LoginState>());
        return;
    }

    if (iChoice == 1)
    {
        string sProductName;
        cout << "Enter product name: ";
        getline(cin, sProductName);
        cin.ignore();
        Product *pProduct = DataManager::getInstance().getProduct(sProductName);
        if (pProduct == nullptr)
        {
            console::printError("Product not found!");
            return;
        }
        else
        {
            console::printSuccess("Product found!");
            console::printNotification("Redirecting to product...");
            console.setCurrentProduct(pProduct);
            console.setState(std::make_unique<ProductState>());
            return;
        }
    }

    if (iChoice == 2)
    {
        string sStoreName = console::inputString("Enter store name: ");
        Store *pStore = DataManager::getInstance().getStore(sStoreName);
        if (pStore == nullptr)
        {
            console::printError("Store not found!");
            return;
        }
        else
        {
            console::printSuccess("Store found!");
            console::printNotification("Redirecting to store...");
            console.setCurrentStore(pStore);
            console.setState(std::make_unique<StoreState>());
            return;
        }
    }

    if (iChoice == 3)
    {
        string sCategoryName = console::inputString("Enter category name: ");
        ProductCategory *pProductCategory = DataManager::getInstance().getProductCategory(sCategoryName);
        if (pProductCategory == nullptr)
        {
            console::printError("Category not found!");
            return;
        }
        else
        {
            console::printSuccess("Category found!");
            console::printNotification("Redirecting to product category...");
            console.setCurrentProductCategory(pProductCategory);
            console.setState(std::make_unique<ProductCategoryState>());
            return;
        }
    }

    if (iChoice == 4)
    {
        console::printNotification("Redirecting to shopping cart...");
        ShoppingCart::getInstance().loadCurrentUsersShoppingCart(console.getCurrentUser());
        console.setState(std::make_unique<ShoppingCartState>());
        return;
    }

    if (iChoice == 5)
    {
        console::printNotification("Redirecting to customer information...");
        console.setState(std::make_unique<CustomerState>());
        return;
    }
}

//==================================================================================================
//============================================= PRODUCT CATEGORY STATE =============================
//==================================================================================================

void ProductCategoryState::display()
{
    console::printPrimaryHeader("Product Category");
    vector<string> vOptions = {"1. View all products", "2. View products by name", "0. Back"};
    console::printOption(vOptions);
}

void ProductCategoryState::handleInput(Console &console)
{
    int iChoice;
    cout << "Enter your choice: ";
    cin >> iChoice;
    cin.ignore();

    if (iChoice < 0 || iChoice > 2)
    {
        console::printError("Invalid choice!");
        return;
    }

    if (iChoice == 0)
    {
        console::printNotification("Redirecting to home page...");
        console.setState(std::make_unique<HomeState>());
        return;
    }

    if (iChoice == 1)
    {
        vector<Product> &vProducts = DataManager::getInstance().getProducts();
        vector<Product> vProductsByCategory;
        for (int i = 0; i < vProducts.size(); i++)
        {
            if (vProducts[i].getCategory() == console.getProductCategory()->getName())
            {
                vProductsByCategory.push_back(vProducts[i]);
            }
        }
        console::printProductList(vProductsByCategory);
        return;
    }

    if (iChoice == 2)
    {
        string sProductName = console::inputString("Enter product name: ");
        Product *pProduct = DataManager::getInstance().getProductByCategory(sProductName, console.getProductCategory()->getName());
        if (pProduct == nullptr)
        {
            console::printError("Product not found!");
            return;
        }
        else
        {
            console::printSuccess("Product found!");
            console::printNotification("Redirecting to product...");
            console.setCurrentProduct(pProduct);
            console.setState(std::make_unique<ProductState>());
            return;
        }
    }
}

//==================================================================================================
//============================================= PRODUCT STATE ======================================
//==================================================================================================

void ProductState::display()
{
    console::printPrimaryHeader("Product");
    vector<string> vOptions = {"1. Add to cart", "2. View product information", "0. Back"};
    console::printOption(vOptions);
}

void ProductState::handleInput(Console &console)
{
    int iChoice;
    cout << "Enter your choice: ";
    cin >> iChoice;
    cin.ignore();

    if (iChoice < 0 || iChoice > 2)
    {
        console::printError("Invalid choice!");
        return;
    }

    if (iChoice == 0)
    {
        console::printNotification("Redirecting to home page...");
        console.setState(std::make_unique<HomeState>());
        return;
    }

    if (iChoice == 1)
    {
        int iQuantity = console::inputInteger("Enter quantity: ");
        console.getShoppingCart()->addProduct(console.getProduct(), iQuantity);
        console::printNotification("Adding product to cart...");
        console::printSuccess("Product added to cart!");
        return;
    }

    if (iChoice == 2)
    {
        console::printNotification("Printing product information...");
        console::printProductInformation(*console.getProduct());
        return;
    }
}

//==================================================================================================
//============================================= STORE STATE ========================================
//==================================================================================================

void StoreState::display()
{
    console::printPrimaryHeader("Store");
    vector<string> vOptions = {"1. View all products", "2. View products by name", "0. Back"};
    console::printOption(vOptions);
}

void StoreState::handleInput(Console &console)
{
    int iChoice;
    cout << "Enter your choice: ";
    cin >> iChoice;
    cin.ignore();

    if (iChoice < 0 || iChoice > 2)
    {
        console::printError("Invalid choice!");
        return;
    }

    if (iChoice == 0)
    {
        console::printNotification("Redirecting to home page...");
        console.setState(std::make_unique<HomeState>());
        return;
    }

    if (iChoice == 1)
    {
        Store *pStore = console.getStore();
        vector<Product *> &vProducts = pStore->getProducts();
        vector<Product> vProductsByStore;
        for (int i = 0; i < vProducts.size(); i++)
        {
            vProductsByStore.push_back(*vProducts[i]);
        }
        console::printNotification("Printing product list...");
        console::printProductList(vProductsByStore);
        return;
    }

    if (iChoice == 2)
    {
        string sProductName = console::inputString("Enter product name: ");
        Product *pProduct = console.getStore()->getProduct(sProductName);
        if (pProduct == nullptr)
        {
            console::printError("Product not found!");
            return;
        }
        else
        {
            console::printSuccess("Product found!");
            console::printNotification("Redirecting to product...");
            console.setCurrentProduct(pProduct);
            console.setState(std::make_unique<ProductState>());
            return;
        }
    }
}

//==================================================================================================
//============================================= SHOPPING CART STATE ================================
//==================================================================================================

void ShoppingCartState::display()
{
    console::printPrimaryHeader("Shopping Cart");
    vector<string> vOptions = {"1. View all products", "2. Increase quantity of product", "3. Decrease quantity of product", "4. Remove product", "5. Checkout", "0. Back"};
    console::printOption(vOptions);
}

void ShoppingCartState::handleInput(Console &console)
{
    int iChoice;
    cout << "Enter your choice: ";
    cin >> iChoice;
    cin.ignore();

    if (iChoice < 0 || iChoice > 5)
    {
        console::printError("Invalid choice!");
        return;
    }

    if (iChoice == 0)
    {
        console::printNotification("Redirecting to home page...");
        console.setState(std::make_unique<HomeState>());
        return;
    }

    if (iChoice == 1)
    {
        const vector<pair<Product *, unsigned int>> vProducts = console.getShoppingCart()->getProducts();
        vector<Product> vProductsByStore;
        for (const auto &pair : vProducts)
        {
            vProductsByStore.push_back(*pair.first);
        }
        console::printNotification("Printing product list...");
        console::printProductList(vProductsByStore);
        return;
    }

    if (iChoice == 2)
    {
        string sProductName = console::inputString("Enter product name: ");
        int iQuantity = console::inputInteger("Enter quantity: ");
        console.getShoppingCart()->increaseQuantity(sProductName, iQuantity);
        console::printNotification("Increasing quantity of product...");
        console::printSuccess("Quantity increased!");
        return;
    }

    if (iChoice == 3)
    {
        string sProductName = console::inputString("Enter product name: ");
        int iQuantity = console::inputInteger("Enter quantity: ");
        console.getShoppingCart()->decreaseQuantity(sProductName, iQuantity);
        console::printNotification("Decreasing quantity of product...");
        console::printSuccess("Quantity decreased!");
        return;
    }

    if (iChoice == 4)
    {
        string sProductName = console::inputString("Enter product name: ");
        Product *pProduct = console.getShoppingCart()->findProduct(sProductName);
        if (pProduct == nullptr)
        {
            console::printError("Product not found!");
            return;
        }
        else
        {
            console.getShoppingCart()->removeProduct(pProduct);
            console::printNotification("Removing product from cart...");
            console::printSuccess("Product removed!");
            return;
        }
    }

    if (iChoice == 5)
    {
        // Check all products in the shopping cart if they quantity is available
        const vector<pair<Product *, unsigned int>> vProducts = console.getShoppingCart()->getProducts();
        for (const auto &[pProduct, uiQuantity] : vProducts)
        {
            if (pProduct->getQuantity() < uiQuantity)
            {
                string sError = "Not enough quantity of " + pProduct->getName() + "!";
                console::printError(sError);
                return;
            }
        }
        console::printNotification("Redirecting to checkout...");
        console.setState(std::make_unique<CheckoutState>());
        return;
    }
}

//==================================================================================================
//============================================= CHECKOUT STATE =====================================
//==================================================================================================

void CheckoutState::display()
{
    console::printPrimaryHeader("Checkout");
    vector<string> vOptions = {"1. Choose payment method", "2. Choose delivery method", "3. Choose discount code", "4. Confirm", "0. Back"};
    console::printOption(vOptions);
}

void CheckoutState::handleInput(Console &console)
{
    int iChoice;
    cout << "Enter your choice: ";
    cin >> iChoice;
    cin.ignore();

    if (iChoice < 0 || iChoice > 4)
    {
        console::printError("Invalid choice!");
        return;
    }

    if (iChoice == 0)
    {
        console::printNotification("Redirecting to shopping cart...");
        ShoppingCart::getInstance().loadCurrentUsersShoppingCart(console.getCurrentUser());
        console.setState(std::make_unique<ShoppingCartState>());
        return;
    }

    if (iChoice == 1)
    {
        console::printNotification("Redirecting to payment method...");
        console::printSecondaryHeader("Choose payment method");
        vector<string> vOptions = {"1. Credit card", "2. Momo"};

        int iChoice_ = console::inputInteger("Enter your choice: ");
        if (iChoice_ < 1 || iChoice_ > 2)
        {
            console::printError("Invalid choice!");
            return;
        }
        PaymentMethod *pPaymentMethod = nullptr;
        if (iChoice_ == 1)
        {
            pPaymentMethod = new CreditCardPayment();
        }
        else
        {
            pPaymentMethod = new MomoPayment();
        }
        console.setCurrentPaymentMethod(pPaymentMethod);
        console::printSuccess("Payment method chosen!");
        return;
    }

    if (iChoice == 2)
    {
        console::printNotification("Redirecting to delivery method...");
        console::printSecondaryHeader("Choose delivery method");
        vector<string> vOptions = {"1. Standard", "2. Express"};
        console::printOption(vOptions);

        int iChoice_ = console::inputInteger("Enter your choice: ");

        if (iChoice_ < 1 || iChoice_ > 2)
        {
            console::printError("Invalid choice!");
            return;
        }

        ShippingStrategy *pShippingStrategy = nullptr;
        if (iChoice_ == 1)
        {
            pShippingStrategy = new StandardShipping();
        }
        else
        {
            pShippingStrategy = new ExpressShipping();
        }

        console.setCurrentShippingStrategy(pShippingStrategy);
        console::printSuccess("Delivery method chosen!");
        return;
    }

    if (iChoice == 3)
    {
        string sDiscountCode = console::inputString("Enter discount code: ");
        DiscountCode *pDiscountCode = DataManager::getInstance().getDiscountCode(sDiscountCode);
        if (pDiscountCode == nullptr)
        {
            console::printError("Discount code not found!");
            return;
        }
        else
        {
            console::printSuccess("Discount code found!");
            console.setCurrentDiscountCode(pDiscountCode);
            console::printNotification("Discount code chosen!");
            return;
        }
        return;
    }

    if (iChoice == 4)
    {
        // Check all products in the shopping cart if they quantity is available
        const vector<pair<Product *, unsigned int>> vProducts = console.getShoppingCart()->getProducts();
        for (const auto &[pProduct, uiQuantity] : vProducts)
        {
            if (pProduct->getQuantity() < uiQuantity)
            {
                string sError = "Not enough quantity of " + pProduct->getName() + "!";
                console::printError(sError);
                return;
            }
        }
        string orderCode = "";
        Order order;
        unsigned int uiTotalQuantity = 0;
        double dTotalPrice = 0;
        for (const auto &[pProduct, uiQuantity] : vProducts)
        {
            uiTotalQuantity += uiQuantity;
            orderCode += std::to_string(uiQuantity);
            dTotalPrice += pProduct->getPrice() * uiQuantity;
        }
        orderCode += std::to_string(uiTotalQuantity);

        order.setOrderCode(orderCode);
        unsigned int day = 30 - uiTotalQuantity % 30;
        unsigned int month = 12 - uiTotalQuantity % 12;
        unsigned int year = 2021 + uiTotalQuantity % 10;
        order.setOrderDate(Date(day, month, year));
        order.setQuantity(uiTotalQuantity);
        order.setTotalPrice(dTotalPrice);

        // Calculate final price

        // Apply discount code
        double dFinalPrice = dTotalPrice;
        if (console.getDiscountCode() != nullptr)
        {
            dFinalPrice = console.getDiscountCode()->applyDiscount(order);
        }

        // Apply shipping strategy
        if (console.getShippingStrategy() != nullptr)
        {
            dFinalPrice += console.getShippingStrategy()->calculateShippingCost(uiTotalQuantity);
        }

        // Apply rank discount

        // Check if the user is a customer
        Customer *pCustomer = dynamic_cast<Customer *>(console.getCurrentUser());
        if (pCustomer != nullptr)
        {
            dFinalPrice = pCustomer->getRank()->applyDiscount(dFinalPrice);
        }

        order.setFinalPrice(dFinalPrice);
        order.setProducts(vProducts);
        order.setShippingStrategy(console.getShippingStrategy());

        // Apply payment method
        console.getPaymentMethod()->processPayment(dFinalPrice);

        // Add order to the user
        pCustomer->addOrder(order);
        return;
    }
}

//==================================================================================================
//============================================= CUSTOMER STATE =====================================
//==================================================================================================

void CustomerState::display()
{
    console::printPrimaryHeader("Customer Information");
    vector<string> vOptions = {"1. View information", "2. View Shopping Cart", "0. Back"};
    console::printOption(vOptions);
}

void CustomerState::handleInput(Console &console)
{
    int iChoice;
    cout << "Enter your choice: ";
    cin >> iChoice;
    cin.ignore();

    if (iChoice < 0 || iChoice > 2)
    {
        console::printError("Invalid choice!");
        return;
    }

    if (iChoice == 0)
    {
        console::printNotification("Redirecting to home page...");
        console.setState(std::make_unique<HomeState>());
        return;
    }

    if (iChoice == 1)
    {
        console::printNotification("Printing customer information...");
        console::printSecondaryHeader("Customer Information");
        console::printUserInformation(*console.getCurrentUser());
        return;
    }

    if (iChoice == 2)
    {
        console::printNotification("Redirecting to shopping cart...");
        ShoppingCart::getInstance().loadCurrentUsersShoppingCart(console.getCurrentUser());
        console.setState(std::make_unique<ShoppingCartState>());
        return;
    }
}

//==================================================================================================
//============================================= EXIT STATE =========================================
//==================================================================================================

void ExitState::display()
{
    console::printPrimaryHeader("Exit");
    vector<string> vOptions = {"1. Save and exit", "2. Exit without saving", "0. Back"};
    console::printOption(vOptions);
}

void ExitState::handleInput(Console &console)
{
    int iChoice;
    cout << "Enter your choice: ";
    cin >> iChoice;
    cin.ignore();

    if (iChoice < 0 || iChoice > 2)
    {
        console::printError("Invalid choice!");
        return;
    }

    if (iChoice == 0)
    {
        console::printNotification("Redirecting to home page...");
        console.setState(std::make_unique<HomeState>());
        return;
    }

    if (iChoice == 1)
    {
        console::printNotification("Saving data...");
        DataManager::getInstance().saveData();
        console::printSuccess("Data saved!");
        console::printNotification("Exiting...");
        exit(0);
        return;
    }

    if (iChoice == 2)
    {
        console::printNotification("Exiting...");
        exit(0);
        return;
    }
}
