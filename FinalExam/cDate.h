#pragma once

#include <string>

using std::string;

/// @brief Date class represents a date
class Date
{
private:
    unsigned int m_uiDay;   ///< Day of the date
    unsigned int m_uiMonth; ///< Month of the date
    unsigned int m_uiYear;  ///< Year of the date

public: // Constructors & Destructor
    Date();
    Date(unsigned int uiDay, unsigned int uiMonth, unsigned int uiYear);
    Date(const Date &other);
    ~Date();

public: // Getters
    unsigned int getDay() const;
    unsigned int getMonth() const;
    unsigned int getYear() const;
    string toString() const;

public: // Setters
    void setDay(unsigned int uiDay);
    void setMonth(unsigned int uiMonth);
    void setYear(unsigned int uiYear);
    void setDate(unsigned int uiDay, unsigned int uiMonth, unsigned int uiYear);
};