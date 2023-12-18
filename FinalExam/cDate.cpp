#include "cDate.h"

//******************************************************************************************************
//************************************ CONSTRUCTORS & DESTRUCTOR ****************************************
//******************************************************************************************************

Date::Date()
{
    m_uiDay = 0;
    m_uiMonth = 0;
    m_uiYear = 0;
}

Date::Date(unsigned int uiDay, unsigned int uiMonth, unsigned int uiYear)
{
    m_uiDay = uiDay;
    m_uiMonth = uiMonth;
    m_uiYear = uiYear;
}

Date::Date(const Date &other)
{
    m_uiDay = other.m_uiDay;
    m_uiMonth = other.m_uiMonth;
    m_uiYear = other.m_uiYear;
}

Date::~Date()
{
}

//******************************************************************************************************
//********************************************** GETTERS ***********************************************
//******************************************************************************************************

unsigned int Date::getDay() const
{
    return m_uiDay;
}

unsigned int Date::getMonth() const
{
    return m_uiMonth;
}

unsigned int Date::getYear() const
{
    return m_uiYear;
}

string Date::toString() const
{
    // If the day or month is less than 10, add a 0 before the number
    string sDay = m_uiDay < 10 ? "0" + std::to_string(m_uiDay) : std::to_string(m_uiDay);
    string sMonth = m_uiMonth < 10 ? "0" + std::to_string(m_uiMonth) : std::to_string(m_uiMonth);
    string sYear = std::to_string(m_uiYear);

    return sDay + "/" + sMonth + "/" + sYear;
}

//******************************************************************************************************
//********************************************** SETTERS ***********************************************
//******************************************************************************************************

void Date::setDay(unsigned int uiDay)
{
    m_uiDay = uiDay;
}

void Date::setMonth(unsigned int uiMonth)
{
    m_uiMonth = uiMonth;
}

void Date::setYear(unsigned int uiYear)
{
    m_uiYear = uiYear;
}

void Date::setDate(unsigned int uiDay, unsigned int uiMonth, unsigned int uiYear)
{
    m_uiDay = uiDay;
    m_uiMonth = uiMonth;
    m_uiYear = uiYear;
}
