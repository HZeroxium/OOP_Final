/**
 * @file iUserManagement.h
 * @brief UserManagement
 *
 */

#pragma once

#include "cUser.h"
#include <memory>
#include <unordered_map>

using std::make_shared;
using std::shared_ptr;
using std::unordered_map;

class UserManager
{
private:
    unordered_map<string, shared_ptr<User>> m_mUsers; ///< Map of users
    shared_ptr<User> m_pCurrentUser;                  ///< Current user
    UserManager() = default;

public: // Singleton methods
    static UserManager &getInstance();
    UserManager(const UserManager &) = delete;
    UserManager &operator=(const UserManager &) = delete;
    ~UserManager() = default;

public: // Authentication methods
    bool login(const string &username, const string &password);
    void logout();
    bool isLoggedIn() const;
    bool addUser(const string &username, const string &password);

public: // Getters
    shared_ptr<User> getCurrentUser() const;
    shared_ptr<User> getUser(const string &username) const;

public: // Setters
    void setCurrentUser(const shared_ptr<User> &user);
};
