#include "uConsoleDecorator.h"

namespace console
{
    void printPrimaryHeader(const string &sHeader)
    {
        unsigned int iHeaderLength = sHeader.length();

        constexpr unsigned int iHeaderWidth = 80;
        constexpr unsigned int iHeaderPadding = 3;
        const unsigned int remainingWidthPerSide = (iHeaderWidth - iHeaderLength - iHeaderPadding) / 2;

        cout << endl;
        cout << string(iHeaderWidth, '=') << endl;
        cout << string(remainingWidthPerSide, '=') << " " << sHeader << " " << string(remainingWidthPerSide + 1, '=') << endl;
        cout << string(iHeaderWidth, '=') << endl;
    }

    void printSecondaryHeader(const string &sHeader)
    {
        unsigned int iHeaderLength = sHeader.length();

        constexpr unsigned int iHeaderWidth = 40;
        constexpr unsigned int iHeaderPadding = 3;
        const unsigned int remainingWidthPerSide = (iHeaderWidth - iHeaderLength - iHeaderPadding) / 2;

        cout << endl;
        cout << string(iHeaderWidth, '-') << endl;
        cout << string(remainingWidthPerSide, '-') << sHeader << string(remainingWidthPerSide + 1, '-') << endl;
        cout << string(iHeaderWidth, '-') << endl;
    }

    void printError(const string &sError)
    {
        cerr << "=> !!! ERROR: " << sError << " !!!" << endl;
    }

    void printSuccess(const string &sSuccess)
    {
        cout << "=> *** SUCCESS: " << sSuccess << " ***" << endl;
    }

    void printOption(const vector<string> &vOptions)
    {
        const int size = vOptions.size();
        cout << "=> Please choose one of the following options (from 0 to " << size - 1 << "): " << endl;
        for (int i = 0; i < vOptions.size(); i++)
        {
            cout << "--> " << vOptions[i] << endl;
        }
    }

    void printNotification(const string &sNotification)
    {
        cout << "#---> NOTIFICATION: " << sNotification << " <---#" << endl;
    }

    void printWarning(const string &sWarning)
    {
        cout << "=> ### WARNING: " << sWarning << " ###" << endl;
    }

    void printProductList(const vector<Product> &vProducts)
    {
        cout << "Product list: " << endl;
        for (int i = 0; i < vProducts.size(); i++)
        {
            cout << i + 1 << ". " << vProducts[i].getName() << endl;
        }
    }

    void printProductInformation(const Product &product)
    {
        cout << "Product information: " << endl;
        cout << "Name: " << product.getName() << endl;
        cout << "Price: " << product.getPrice() << endl;
        cout << "Quantity: " << product.getQuantity() << endl;
        cout << "Category: " << product.getCategory() << endl;
        cout << "FLASH SALE: " << (product.getFlashSaleStatus() ? "Yes" : "No") << endl;
    }

    void printUserInformation(const User &user)
    {
        cout << "User information: " << endl;
        cout << "Name: " << user.getUsername() << endl;
        cout << "Email: " << user.getEmail() << endl;
        cout << "Phone: " << user.getPhoneNumber() << endl;
        cout << "Date of birth: " << user.getBirthDate().toString() << endl;
        cout << "Join date: " << user.getJoinDate().toString() << endl;
    }

    string inputString(const string &sMessage)
    {
        string sInput;
        cout << sMessage;
        std::getline(std::cin, sInput);
        std::cin.ignore();
        return sInput;
    }

    int inputInteger(const string &sMessage)
    {
        int iInput;
        cout << sMessage;
        std::cin >> iInput;
        std::cin.ignore();
        return iInput;
    }
}