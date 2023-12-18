#include "uConsoleDecorator.h"

namespace console
{
    void printPrimaryHeader(const string &sHeader)
    {
        cout << endl;
        cout << "========================================" << endl;
        cout << sHeader << endl;
        cout << "========================================" << endl;
    }

    void printSecondaryHeader(const string &sHeader)
    {
        cout << endl;
        cout << "----------------------------------------" << endl;
        cout << sHeader << endl;
        cout << "----------------------------------------" << endl;
    }

    void printError(const string &sError)
    {
        cerr << "Error: " << sError << endl;
    }

    void printSuccess(const string &sSuccess)
    {
        cout << "Success: " << sSuccess << endl;
    }

    void printOption(const vector<string> &vOptions)
    {
        cout << "Options: " << endl;
        for (int i = 0; i < vOptions.size(); i++)
        {
            cout << i + 1 << ". " << vOptions[i] << endl;
        }
    }

    void printNotification(const string &sNotification)
    {
        cout << "Notification: " << sNotification << endl;
    }

    void printWarning(const string &sWarning)
    {
        cout << "Warning: " << sWarning << endl;
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