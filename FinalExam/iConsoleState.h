/**
 * @file iConsoleState.h
 * @brief Definition of the ConsoleState class representing a state of the console using State Pattern
 *
 * This file contains definitions of the ConsoleState class representing a state of the console using State Pattern.
 */

#pragma once

#include "cConsole.h"

/// @brief State interface of the State Pattern
class ConsoleState
{
public:
    virtual void display() = 0;
    virtual void handleInput(Console &console) = 0;
    virtual ~ConsoleState() = default;
};

/// @brief Concrete state of the State Pattern for Login screen
class LoginState : public ConsoleState
{
public:
    void display() override;
    void handleInput(Console &console) override;
};

/// @brief Concrete state of the State Pattern for Home screen
class HomeState : public ConsoleState
{
public:
    void display() override;
    void handleInput(Console &console) override;
};

/// @brief Concrete state of the State Pattern for Product Category screen
class ProductCategoryState : public ConsoleState
{
public:
    void display() override;
    void handleInput(Console &console) override;
};

/// @brief Concrete state of the State Pattern for Store screen
class StoreState : public ConsoleState
{
public:
    void display() override;
    void handleInput(Console &console) override;
};

/// @brief Concrete state of the State Pattern for Product screen
class ProductState : public ConsoleState
{
public:
    void display() override;
    void handleInput(Console &console) override;
};

/// @brief Concrete state of the State Pattern for Shopping Cart screen
class ShoppingCartState : public ConsoleState
{
public:
    void display() override;
    void handleInput(Console &console) override;
};

/// @brief Concrete state of the State Pattern for Customer screen
class CustomerState : public ConsoleState
{
public:
    void display() override;
    void handleInput(Console &console) override;
};

/// @brief Concrete state of the State Pattern for Order screen
class OrderState : public ConsoleState
{
public:
    void display() override;
    void handleInput(Console &console) override;
};

/// @brief Concrete state of the State Pattern for Checkout screen
class CheckoutState : public ConsoleState
{
public:
    void display() override;
    void handleInput(Console &console) override;
};

/// @brief Concrete state of the State Pattern for Exit screen
class ExitState : public ConsoleState
{
public:
    void display() override;
    void handleInput(Console &console) override;
};
