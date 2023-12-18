#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "cProduct.h"

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::vector;

/// @brief Namespace for screen printing functions
namespace console
{
    void printPrimaryHeader(const string &sHeader);
    void printSecondaryHeader(const string &sHeader);
    void printError(const string &sError);
    void printSuccess(const string &sSuccess);
    void printOption(const vector<string> &vOptions);
    void printNotification(const string &sNotification);
    void printWarning(const string &sWarning);

    void printProductList(const vector<Product> &vProducts);
    void printProductInformation(const Product &product);
    void printUserInformation(const User &user);
    string inputString(const string &sMessage);
    int inputInteger(const string &sMessage);

};