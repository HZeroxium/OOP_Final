#include "iUserManagement.h"

//********************************************************************************************************************
//************************************ SINGLETON METHODS *************************************************************
//********************************************************************************************************************

UserManager &UserManager::getInstance()
{
    static UserManager instance;
    return instance;
}

//********************************************************************************************************************
//************************************ AUTHENTICATION METHODS ********************************************************
//********************************************************************************************************************

bool UserManager::login(const string &username, const string &password)
{
    if (m_mUsers.find(username) == m_mUsers.end())
    {
        return false;
    }
    if (m_mUsers[username]->getPassword() != password)
    {
        return false;
    }
    m_pCurrentUser = m_mUsers[username];
    return true;
}

void UserManager::logout()
{
    m_pCurrentUser = nullptr;
}

bool UserManager::isLoggedIn() const
{
    return m_pCurrentUser != nullptr;
}

bool UserManager::addUser(const string &username, const string &password)
{
    if (m_mUsers.find(username) != m_mUsers.end())
    {
        return false;
    }
    m_mUsers[username] = make_shared<User>(username, password);
    return true;
}

//********************************************************************************************************************
//************************************ GETTERS ***********************************************************************
//********************************************************************************************************************

shared_ptr<User> UserManager::getCurrentUser() const
{
    return m_pCurrentUser;
}

shared_ptr<User> UserManager::getUser(const string &username) const
{
    if (m_mUsers.find(username) == m_mUsers.end())
    {
        return nullptr;
    }
    return m_mUsers.at(username);
}

//********************************************************************************************************************
//************************************ SETTERS ***********************************************************************
//********************************************************************************************************************

void UserManager::setCurrentUser(const shared_ptr<User> &user)
{
    m_pCurrentUser = user;
}
