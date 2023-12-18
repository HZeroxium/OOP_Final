#include "cReview.h"

//***********************************************************************************
//************************************** CONSTRUCTORS & DESTRUCTOR ******************
//***********************************************************************************

/// @brief Default constructor
Review::Review()
{
    m_uiRating = 0;
    m_sComment = "";
}

/// @brief Constructor with parameters
/// @param uiRating Rating of the review
/// @param sComment Comment of the review
Review::Review(unsigned int uiRating, const string &sComment)
{
    m_uiRating = uiRating;
    m_sComment = sComment;
}

/// @brief Copy constructor
/// @param other Review object to copy from
Review::Review(const Review &other)
{
    m_uiRating = other.m_uiRating;
    m_sComment = other.m_sComment;
}

//***********************************************************************************
//************************************** GETTERS & SETTERS **************************
//***********************************************************************************

/// @brief Get the rating of the review
/// @return Rating of the review
unsigned int Review::getRating() const
{
    return m_uiRating;
}

/// @brief Get the comment of the review
/// @return Comment of the review

string Review::getComment() const
{
    return m_sComment;
}

/// @brief Set the rating of the review
/// @param uiRating Rating of the review

void Review::setRating(unsigned int uiRating)
{
    m_uiRating = uiRating;
}

/// @brief Set the comment of the review
/// @param sComment Comment of the review

void Review::setComment(const string &sComment)
{
    m_sComment = sComment;
}
